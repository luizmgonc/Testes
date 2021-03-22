
#include <stdio.h>
#include <stdint.h>

typedef struct Edrv_Act_1{
	uint8_t Checksum_actual_torque;
	uint8_t Alive_counter_actual_torque;
	uint8_t Actual_run_state;
	uint8_t Actual_operation_mode;
	uint16_t Actual_torque;
	uint16_t Actual_speed;
	uint16_t Actual_voltage;
	uint16_t Actual_dc_current;
	uint8_t msg[8];
    uint8_t can_id;
	uint8_t flag_rx;

}Edrv_Act_1;

void organizar_mensagens_rx(Edrv_Act_1 *a){

    a->Checksum_actual_torque = a->msg[0];
    a->Alive_counter_actual_torque = a->msg[1] >> 4;
    a->Actual_run_state = (a->msg[1] & 0b00001100) >> 2;
    a->Actual_operation_mode = ((a->msg[1] & 0b00000011) << 2) + ((a->msg[2] & 0b11000000) >> 6);
    a->Actual_torque = ((a->msg[2] & 0b00111111) << 6) + ((a->msg[3] & 0b11111100) >> 2);
    a->Actual_speed = ((a->msg[3] & 0b00000011) << 11) + (a->msg[4] << 3) + ((a->msg[5] & 0b11100000) >> 5);
    a->Actual_voltage = ((a->msg[5] & 0b00001111) << 6) + ((a->msg[6] & 0b11111100) >> 2);
    a->Actual_dc_current = ((a->msg[6] & 0b00000011) << 8) + a->msg[7];
}


int main(){

    Edrv_Act_1 teste;
    teste.msg[0] = 0b01110100;
    teste.msg[1] = 0b10100101;
    teste.msg[2] = 0b10000000;
    teste.msg[3] = 0b01100001;
    teste.msg[4] = 0b10010001;
    teste.msg[5] = 0b00100000;
    teste.msg[6] = 0b10111000;
    teste.msg[7] = 0b01010000;

    organizar_mensagens_rx(&teste);

    printf("Checksum actual torque: %d\n", teste.Checksum_actual_torque);

    printf("Alive counter actual torque: %d\n", teste.Alive_counter_actual_torque);

	printf("Actual run state: %d", teste.Actual_run_state);

	if(teste.Actual_run_state == 0){
		printf(" (Pre-Run)\n");
	}else if(teste.Actual_run_state == 1){
		printf(" (Run)\n");
	}else if(teste.Actual_run_state == 2){
		printf(" (Post-Run)\n");
	}else if(teste.Actual_run_state == 3){
		printf(" (Post-Run Finished)\n");
	}
	
	printf("Actual operation mode: %d", teste.Actual_operation_mode);

	if(teste.Actual_operation_mode == 0x0){
		printf(" (Idle)\n");
	}else if(teste.Actual_operation_mode == 0x1){
		printf(" (Torque Mode)\n");
	}else if(teste.Actual_operation_mode == 0x4){
		printf(" (Voltage Mode)\n");
	}else if(teste.Actual_operation_mode == 0x6){
		printf(" (Speed Mode)\n");
	}else if(teste.Actual_operation_mode == 0xB){
		printf(" (Start Mode)\n");
	}else if(teste.Actual_operation_mode == 0xE){
		printf(" (Stand-by)\n");
	}else if(teste.Actual_operation_mode == 0xF){
		printf(" (Failure)\n");
	}
	
	printf("Actual torque: %d Nm\n",teste.Actual_torque);

	printf("Actual speed: %d rpm\n",teste.Actual_speed);

	printf("Actual DC voltage: %d V\n", teste.Actual_voltage);

	printf("Actual DC current: %d A\n", teste.Actual_dc_current);
}