#pragma warning(disable:4996)
#include<stdio.h>
#include<stdlib.h>

int maxwat;
void maxflow(int* height, int* maxpoint, int begin, int end);

int main(void){
	int N;
	int i;
	do{
		scanf("%d", &N);
		if (N <= 0)
			break;
		int * height = (int *) malloc(sizeof(int) * N);
		for (i = 0; i < N; i++)
			scanf("%d", &height[i]);
		if (N <= 2){
			printf("0\n");
			continue;
		}
		int * maxpoint = (int *) malloc(sizeof(int) * N);
		int j = 0;
		if (height[0] > height[1])
			maxpoint[j++] = 0;
		for (i = 1; i < N - 1; i++)
			if (height[i] >= height[i - 1] && height[i] >= height[i + 1])
				maxpoint[j++] = i;
		if (height[N-1] > height[N-2])
			maxpoint[j++] = N-1;
		if (j <= 1){
			printf("0\n");
			continue;
		}
		maxwat = 0;
		maxflow(height, maxpoint, 0, j - 1);
		printf("%d\n", maxwat);
		free(maxpoint);
		free(height);
	} while (true);
	return 0;
}
void maxflow(int* height, int* maxpoint, int begin, int end){
	int maximal = 0;
	int maximal2 = 0;
	int maxvalue = 0;
	int i;
	int j;
	int k;
	if (maxpoint[end] - maxpoint[begin] > 1){
		for (i = begin; i <= end; i++){
			if (height[maxpoint[i]] > maxvalue){
				maxvalue = height[maxpoint[i]];
				maximal = maxpoint[i];
			}
		}
		for (k = begin; k <= end; k++)
			if (height[maxpoint[k]] == maxvalue)
				break;
		i = k;
		maxvalue = 0;
		for (j = begin; j <= end; j++){
			if (height[maxpoint[j]] > maxvalue && maxpoint[j] != maximal){
				maxvalue = height[maxpoint[j]];
				maximal2 = maxpoint[j];
			}
		}
		for (k = begin; k <= end; k++)
			if (height[maxpoint[k]] == maxvalue && k != i)
				break;
		j = k;
		if (maximal > maximal2){
			for (k = maximal2 + 1; k < maximal; k++){
				if (height[maximal2] - height[k] > 0){
					maxwat = maxwat + height[maximal2] - height[k];
				}
			}
			maxflow(height, maxpoint, begin, j);
			maxflow(height, maxpoint, i, end);
		}
		else if (maximal < maximal2){
			for (k = maximal + 1; k < maximal2; k++){
				if (height[maximal2] - height[k] > 0){
					maxwat = maxwat + height[maximal2] - height[k];
				}
			}
			maxflow(height, maxpoint, begin, i);
			maxflow(height, maxpoint, j, end);
		}
	}
}