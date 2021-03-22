
#include <stdio.h>
#include <stdint.h>

typedef struct Pt_Edrv_Des_1{
	uint8_t Checksum_torque_request;     		//não usado
	uint8_t Alive_counter_torque_request;		//não usado
	uint8_t Operation_mode_request;
	uint16_t Torque_request;					// && Maximum allowed torque
	uint16_t Minimum_allowed_torque;
	uint16_t Speed_request;
	uint8_t msg[7];
	uint8_t can_id;
	uint8_t flag;
}Pt_Edrv_Des_1;

void organizar_mensagens_tx(Pt_Edrv_Des_1 *a){

	a->msg[0] = a->Checksum_torque_request;
	a->msg[1] = (a->Alive_counter_torque_request << 4) + a->Operation_mode_request;
	a->msg[2] = a->Torque_request >> 4;
	a->msg[3] = ((a->Torque_request & 0b0000000000001111) << 4) + (a->Minimum_allowed_torque >> 8);
	a->msg[4] =	a->Minimum_allowed_torque & 0b0000000011111111;
	a->msg[5] =	a->Speed_request >> 5;
	a->msg[6] = (a->Speed_request & 0b0000000000011111) << 3;


}


int main(){

    Pt_Edrv_Des_1 teste;
    teste.Checksum_torque_request = 116;
    teste.Alive_counter_torque_request = 10;
    teste.Operation_mode_request = 6;
    teste.Torque_request = 24;
    teste.Minimum_allowed_torque = 0;
    teste.Speed_request = 3209;

    organizar_mensagens_tx(&teste);

	for(int i = 0; i<7; i ++){
		printf("Mensagem %d: %d\n", i, teste.msg[i]);
	}
}