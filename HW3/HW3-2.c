#include <omp.h>

int foo(int N, int *a, int *b, int *c, int *d)
{
	
	double tmp, total = 0;
	#pragma omp parallel
	{
		#pragma omp sections
	
	//#pragma omp sections 안에서는 #pragma omp section으로 task를 병렬하여 작업한다.
		#pragma omp section
	//
		{
			//loop를 병렬화할 때, total이라는 변수에 여러 스레드가 접근하는 것을 방지하기 위해 reduction을 이용해준다.
			//#pragma omp for
			#pragma omp parallel for reduction(+:total)
			for(int i=0; i<N; t++)
			{
				a[b[i]] += b[i];
				total += b[i];
			}
		}
		#pragma omp section
		{
			//#pragma omp for
			//tmp를 private로 설정해서 thread들이 독립적으로 tmp를 사용해야 한다.
			#pragma omp parallel for private(tmp) reduction(+:total)
			
			#pragma omp for nowait
			for(int i=0; i<N; i++)
			{
				tmp = c[i];
				c[i] = d[i];
				d[i] = tmp;
				total += c[i];
			}
			#pragma omp for nowait
			for(int i=0; i<N; i++)
			{
				total += d[i];
			}
		}
	}
	return total;
}
