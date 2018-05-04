#include <string.h>
#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include "pmlib.h"
#include "line.h"

/* Main */
int main(int argc, char** argv){
	server_t servidor;
	counter_t contador;
	line_t lineas;
	device_t disp;
	char **lista;
	int i_, num_devices_;
	int frequency= 0;
	int aggregate= 0;

	LINE_CLR_ALL(&lineas);
	pm_set_lines("0-4", &lineas);
	printf("Empieza pm_set_server\n");
	pm_set_server("127.0.0.1", 6526, &servidor);

	pm_get_devices(servidor, &lista, &num_devices_);  //Lista ser‡ una lista de nombres de dispositivos separados por comas
	pm_create_counter("TegraDevice", lineas, aggregate, frequency, servidor, &contador);

	pm_start_counter(&contador);

	// CODE TO ANALIZE

	pm_stop_counter(&contador);
	pm_get_counter_data(&contador);

	pm_print_data_csv("outdata.csv", contador, lineas, -1);
	pm_finalize_counter( &contador );

	return 0;
}

