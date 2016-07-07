#include <ctype.h>
#include <getopt.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_BURNERS 1000

pthread_t printer;
pthread_t burner[MAX_BURNERS];

void * printer_routine(void *arg) {
	int count = 0;
	char timebuf[256];
	while (1) {
		time_t now = time(NULL);
		ctime_r(&now, timebuf);
		printf("Count: %d, %s", count, timebuf);
		count++;
		sleep(1);
	}
}

void * reader_routine(void *arg) {
	while (1) {
		getchar();
	}
}

void * burner_routine(void *arg) {
	volatile int count = 0;
	while (1) {
		count++;
	}
}

void print_usage() {
	fprintf(stderr, "Usage: stress reader_count burner_count\n");
}

int main(int argc, char *argv[]) {
	int reader_count, burner_count;
	pthread_t *burner_threads;
	pthread_t *reader_threads;

	if (argc != 3) {
		print_usage();
		return EXIT_FAILURE;
	}

	if (sscanf(argv[1], "%d", &reader_count) != 1) {
		print_usage();
		return EXIT_FAILURE;
	}

	if (sscanf(argv[1], "%d", &burner_count) != 1) {
		print_usage();
		return EXIT_FAILURE;
	}

	reader_threads = calloc(reader_count, sizeof(pthread_t));
	burner_threads = calloc(burner_count, sizeof(pthread_t));

	for (int i = 0; i < burner_count; i++) {
		pthread_create(&burner_threads[i], NULL, &burner_routine, NULL);
	}

	for (int i = 0; i < reader_count; i++) {
		pthread_create(&reader_threads[i], NULL, &reader_routine, NULL);
	}

	pthread_create(&printer, NULL, &printer_routine, NULL);
	pthread_join(printer, NULL);
	return 0;
}
