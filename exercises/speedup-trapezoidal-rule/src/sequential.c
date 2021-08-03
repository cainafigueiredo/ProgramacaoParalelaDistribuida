#include <stdio.h>
#include <math.h>
#include <sys/time.h>

double f(double x) { /* Calcula f(x). */
	double return_val;
	return_val=exp(x);
	return return_val;
}

int main(int argc, char *argv[]) { /* trapezio_seq.c */
	double integral; /* integral armazena resultado final */
	double a = 0.0, b = 1.0; /* a, b - limite esquerdo e direito da função */
	long int i,n; /* n - número de trapezóides */
	n = 100000000;
	double x, h; /* h - largura da base do trapezóide */
	struct timeval tempo_inicial, tempo_final, tempo_gasto;
	//printf("Entre a, b, e n \n");
	//scanf("%lf %lf %ld", &a, &b, &n);
	h = (b-a)/n;
	gettimeofday(&tempo_inicial, NULL);
	integral = (f(a) + f(b))/2.0;
	x = a;
	for (i = 1; i < n; i++) {
		x += h;
		integral += f(x);
	}
	integral *= h;
	gettimeofday(&tempo_final, NULL);
	timersub(&tempo_final, &tempo_inicial, &tempo_gasto);
	printf("Foram gastos %3.1f segundos\n", (double) tempo_gasto.tv_sec + (double) (tempo_gasto.tv_usec/1000000.0));
	printf("Com n = %ld trapezóides, a estimativa \n", n);
	printf("da integral de %lf até %lf = %lf \n", a, b, integral);
	return(0);
}

