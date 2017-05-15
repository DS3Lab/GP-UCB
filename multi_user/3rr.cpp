#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <string.h>
#include <sstream>
#include <math.h> 
#include <Eigen/Eigen>

#define ALGO 9
#define PRIOR_DATASET 19
#define TEST_DATASET 4
#define ITERATION 9
#define USER 4          // how many users
#define SCALE_FACTOR 0.5 // scale factor of kernel matrix

using namespace Eigen;
using namespace std;

double prior_accu[PRIOR_DATASET+5][ALGO+5];
// the prior_accu is seen by our system, but different users can only see different parts of the data

double prior_mean[USER+5][ALGO+5];
double prior_cov[USER+5][ALGO+5][ALGO+5];

double observe_accu[TEST_DATASET+5][ALGO+5];
double beta[ALGO*100];
double current_mean[USER+5][ALGO+5];
double current_var[USER+5][ALGO+5];
double pre_var[USER+5][ALGO+5];
double kernel[USER+5][ALGO+5][ALGO+5];
double y[1000]; // at each tiem t, we only choose one dataset/user to update
double sigma_t_k[USER+5][100];
double sigma_t[USER+5][100][100];
int a[USER+5][100]; // is the actual events that happen in the process
double C_t[USER+5][100][100]; // 10000 is time t;
int result[USER+5][ALGO+5]; // is the result that we predict
int max_iteration; // max_iteration can be shared among multiple users
int has_chosen[USER+5][ALGO+5];
double cost[ALGO+5];
int has_sample[USER+5];
int has_run[USER+5][ALGO+5];


double const sigma = 0.5;
double const gaussian_noise = 0.01;

void my_cin(string f)
{
	ifstream fin(f);
	for (int i=0; i < PRIOR_DATASET; i++)
		for (int j = 0; j < ALGO ; j++)
			fin >> prior_accu[i][j];
}

void cin_cost(string f)
{
	ifstream fin(f);
	double tmp_cost[100][100];
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < ALGO; j++)
		{
			fin >> tmp_cost[i][j];
		}
	}
	for (int i = 0; i < ALGO; i++)
	{
		double sum_ = 0;
		for (int j = 0; j < 10; j++)
			sum_ += tmp_cost[j][i];
		cost[i] = sum_ * 1.0 / 10;
 	}
}


// for user a, we calculate his own prior Gaussian
void calculate_prior_gaussian(int a)
{
	memset(prior_mean[a], 0, sizeof(prior_mean[a]));
	memset(prior_cov[a], 0, sizeof(prior_cov[a]));

	cout << "prior mean for user " << a << " is:" << endl;

	for (int i = 0; i < ALGO; i++)
	{
		int num_data = 0;
		prior_mean[a][i] = 0;
		for (int j = 0; j < PRIOR_DATASET; j++)
		{
			if (j % USER == a || j % USER == a + 1 || j % USER == a + 2)
			{
				prior_mean[a][i] += prior_accu[j][i];
				num_data = num_data+1;
			}
		}
		prior_mean[a][i] = prior_mean[a][i] * 1.0 / num_data;
		cout << prior_mean[a][i] << " " << endl;
	}
	cout << endl << endl;
	cout << "-----------------------------------------------" << endl;
	cout << "kernel matrix for user " << a << " is:" << endl;
	for (int i = 0; i < ALGO; i++)
	{
		for (int j = 0; j < ALGO; j++)
		{
			double dis = 0;
			int num_data = 0;
			for (int k = 0; k < PRIOR_DATASET; k++)
			{
				if (k % USER == a || k % USER == a + 1 || k % USER == a + 2)
				{
					dis += (prior_accu[k][i]-prior_accu[k][j])*(prior_accu[k][i] - prior_accu[k][j]);
					num_data = num_data+1;
				}
			}
			kernel[a][i][j] = SCALE_FACTOR * exp((-1)*dis*1.0/0.5);
			//kernel[i][j] = 1;
			cout << kernel[a][i][j] << " ";
		}
		cout << endl;
	}
	cout << "-----------------------------------------------" << endl;
}

void cin_test(string f)
{
	ifstream fin(f);
	string test_line;
	double accu;
	int i = 0;
	while (getline(fin, test_line))
	{
		istringstream stream(test_line);   
		int j = 0; 
		while (stream >> accu)  
		{
			// observe_accu[i][j]: simulates the observed quality in the i-th time by the j-th algorithm
			// i starts from 1

			observe_accu[i][j] = double(accu);
			cout << "observed accuracy for user " << i << " with algorithm " << j << " is: " << observe_accu[i][j] << endl;
			j++;
		}			 
		i++;
	}
}

void init()
{
	for (int i = 0; i < USER; i++)
		for (int j = 0; j < ALGO; j++)
			current_mean[i][j] = prior_mean[i][j];

	cout << "variance is: " << endl;
	for (int j = 0; j < USER; j++)
	{
		for (int i = 0; i < ALGO; i++)
		{
			current_var[j][i] = kernel[j][i][i] * 1.0;
			cout << current_var[j][i] << " " << endl;
		}
	}

	for (int j = 0; j < USER; j++)
		for (int i = 0; i < ALGO; i++)
			has_chosen[j][i] = 0;
	
	for (int i = 0; i < USER; i++)
		has_sample[i] = 1;

	for (int j = 0; j < USER; j++)
		for (int i = 0; i < ALGO; i++)
			has_run[j][i] = 0;

	max_iteration = ITERATION;
}

// generate the Gaussian noise ~ N (mu, sigma * sigma)

double generate_gaussian_noise(double mu, double sigma)
{
	const double epsilon = std::numeric_limits<double>::min();
	const double two_pi = 2.0 * 3.14159265358979323846;

	static double z0, z1;

	static bool generate;
	generate = !generate;

	double u1, u2;
	do
	{
		u1 = rand() * (1.0 / RAND_MAX);
		u2 = rand() * (1.0 / RAND_MAX);

	} while (u1 <= epsilon); // in case u1 is 0

	z0 = sqrt(-2.0 * log(u1)) * cos(two_pi * u2);
	z1 = sqrt(-2.0 * log(u2)) * sin(two_pi * u1);

	cout << "the gaussian noise generated randomly is: " << z0 * sigma + mu << endl;
	
	return z0 * sigma + mu;
}

int main(int argc, char const *argv[])
{
	my_cin(argv[1]);  // cin prior accuracy to construct prior information
	for (int i = 0; i < USER; i++)
	{
		calculate_prior_gaussian(i);
	}
	cin_test(argv[2]); // multiplt users, each dataset is a user
	cin_cost(argv[3]);
	init();

	//for (int i = 0; i < ALGO; i++)
	//	current_mean[i] = 0.8;

	cout << endl;

	ofstream fout("2rr_2031.txt");

	int t = 1;

	//if (observe > 0)
	//	fout << endl
	while (1) // 
	{
		cout << "Iteration: " << t << endl;
	
		// pick up the best algo for every user
		// a[][] is used to update, while result is used to update the results that will be reported
		for (int j = 0; j  < USER; j++)
		{
			int algo = -1; 
			double max_reward = -1000000.0;

			beta[t] = log(ALGO * has_sample[j] * has_sample[j] * 1.0 /sigma);
			cout << beta[t] << endl;
	
			for (int i = 0; i < ALGO; i++)
			{
				// choose a 'best' algorithm based on the previous accuracy and covariance information
				// beta[t] is responsible for the balance between exploration and exploitation
				
				double tmp_reward = current_mean[j][i] + sqrt(beta[t]*1.0/cost[i]) * sqrt(current_var[j][i]);
				cout << "tmp_reward is: " << tmp_reward << endl;
				if (tmp_reward > max_reward && has_run[j][i] == 0)
				{
					max_reward = tmp_reward;
					algo = i;
				}
			}
			has_chosen[j][algo] = 1;
			
			cout << algo+1 <<" has been chosen by user " << j << endl;
			a[j][t] = algo; // we use the actuall one to update		
			
		}
		
		int user_id = 0;
	
		/*if (t == 1)
		{
			// find the max user id
			double max_sigma = 0;
			for (int i = 0; i < USER; i++)
				if (sqrt(current_var[i][a[t][i]]) > max_sigma)
				{					
					max_sigma = sqrt(current_var[i][a[t][i]]);
					user_id = i;
				}
		}
		else
		{
			// find the max user id
			double max_sigma = -10000000.0;
			for (int i = 0; i < USER; i++)
				if ((sqrt(current_var[i][a[t][i]]) -  sqrt(pre_var[i][a[t-1][i]]))> max_sigma)
				{					
					max_sigma = sqrt(current_var[i][a[t][i]]) - sqrt(pre_var[i][a[t-1][i]]);
					user_id = i;
				}
		}*/
		if (t % 8 == 1 || t % 8 == 2)
			user_id = 2;
		else if (t % 8 == 3 || t % 8 == 4)
			user_id = 0;
		else if (t % 8 == 5 || t % 8 == 6)
			user_id = 3;
		else
			user_id = 1;

		// to do: add to prevent the user has run all algorithms and continue running

		has_run[user_id][a[user_id][t]] = 1;
		has_sample[user_id] += 1;

		fout << user_id << " " << a[user_id][t] << endl;

		y[t] = observe_accu[user_id][a[user_id][t]] + gaussian_noise;
		cout << "observe_accu is: " << observe_accu[user_id][a[user_id][t]] << " " << "noise is: " << gaussian_noise << endl;

		for (int i = 0; i < USER; i++)
			for (int j = 0; j < t; j++)
					for (int k = 0; k < t; k++)
						sigma_t[i][j][k] = kernel[i][a[i][j+1]][a[i][k+1]];

		for (int i = 0; i < USER; i++)
			for (int j = 0; j < t; j++)
			{
				for (int k= 0; k < t; k++)
				{
					if (j == k)
						C_t[i][j][k] = sigma_t[i][j][k] + gaussian_noise * gaussian_noise;
					else
						C_t[i][j][k] = sigma_t[i][j][k];
				}
			}

			// compute (C_t)-reverse
		for (int i = 0; i < USER; i++)
		{
			MatrixXd C_t_eigen(60, 60);
			for (int j = 0; j < 60; j++)
				for (int k = 0; k < 60; k++)
				{
					if (j < t && k < t)
						C_t_eigen(j,k) = C_t[i][j][k];
					else if (j == k)
						C_t_eigen(j,k) = 1;
					else
						C_t_eigen(j,k) = 0;
				}
			C_t_eigen = C_t_eigen.inverse();

		

			for (int j = 0; j < t; j++)
			{
				for (int k = 0; k < t; k++)
				{
					C_t[i][j][k] = C_t_eigen(j,k);
				}
			}
		}

		for (int u = 0; u < USER; u++)
		{
			for (int i = 0; i < ALGO; i++)
			{
				// update mean_[i]
				for (int j = 0; j < t; j++)
					sigma_t_k[u][j] = kernel[u][a[u][j+1]][i];
	
				double tmp[10000];
				for (int j = 0; j < t; j++)
				{
					tmp[j] = 0;
					for (int k = 0; k < t; k++)
						tmp[j] += sigma_t_k[u][k] * C_t[u][k][j];
				}
		
				cout << "updated mean is: ";
				if (u == user_id)
				{
					current_mean[u][i] = 0;
					for (int j = 0; j < t; j++)
					{
						current_mean[u][i] += tmp[j]* y[j+1];
					
					}
					cout << current_mean[u][i] << " ";
				}
				
	
				// update cov
				double update = 0;
				if (u == user_id)
				{
					for (int j = 0; j < t; j++)
						update += tmp[j] * kernel[user_id][a[user_id][j+1]][i];
					pre_var[u][i] = current_var[u][i];
					current_var[u][i] = kernel[u][i][i] - update;
				}
			}
		}
		cout << endl;
		cout << "updated variance is: " << endl;;
		for (int j = 0; j < USER; j++)
		{
			for (int i = 0; i < ALGO; i++)
				cout << current_var[j][i]<< " ";
			cout << endl;
		}
		cout << endl;
		
		t++;

		int flag = 0;
		for (int j = 0; j < USER; j++)
			for (int k = 0; k < ALGO; k++)
				if (has_run[j][k] == 0)
				{
					flag = 1;
					break;
				}
		if (flag == 0)
			break;
	}


	fout.close();

	return 0;
}