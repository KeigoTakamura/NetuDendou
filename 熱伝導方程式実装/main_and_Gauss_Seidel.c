#include<stdio.h>
#include<math.h>
#include<time.h>
#define M 200
#define N 400 //x
#define mini 0.005
#define big 0.01
#define max_try 50000
#define sum_latteice 800000
#define e 1.0E-10



int main() {
	double temp_lay[N][M];
	double he = 2.0;
	double wh = 1.0;
	double lattice_size = mini;
	double sum_delta = 0.0;
	double delta = 0.0;
	FILE *fp1;
	//FILE *fp2;

	time_t time_test = time(NULL);

	for (size_t i = 0; i < N; i++)
	{
		for (size_t t = 0; t < M; t++)
		{
			temp_lay[i][t] = 0.00;//二次元平面初期化
		}
	}



	for (size_t i = 0; i < N; i++)//初期状態温度設定 x軸
	{
		temp_lay[0][i] = 1.0;//上端温度設定
		temp_lay[M - 1][i] = -1.0;//下端温度設定
	}
	for (size_t i = 0; i < M; i++)//初期状態設定 y軸
	{
		temp_lay[i][0] = -1.0;//右端部温度設定
		temp_lay[i][N - 1] = -1.0;//左端部温度設定
	}





	for (size_t cout = 0; cout < max_try; cout++)
	{

		sum_delta = 0.0;
		for (size_t i = 1; i < M - 1; i++)
		{
			for (size_t t = 1; t < N - 1; t++)
			{
				delta = temp_lay[i][t];
				temp_lay[i][t] = (temp_lay[i][t - 1] + temp_lay[i - 1][t] + temp_lay[i][t + 1] + temp_lay[i + 1][t])*0.25;
				sum_delta += (temp_lay[i][t] - sum_delta)*(temp_lay[i][t] - sum_delta);
			}

		}


		if (sum_delta / (M*N) < e) {
			break;
		}

	}

	printf("time_test %d \n",time(NULL) - time_test);

	fopen_s(&fp1,"date_2dmap.txt", "w+");


	for (size_t i = 0; i < M; i++)
	{
		for (size_t t = 0; t < N; t++)
		{
			fprintf(fp1, "%lf %lf %lf \n", (double)i*mini, (double)t*mini, temp_lay[i][t]);
		}
		fprintf(fp1, "\n");
	}

	fclose(fp1);











	return 0;
}