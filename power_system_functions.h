//
// Created by rafael on 03/02/26.
//

#ifndef POWER_SYSTEM_FUNCTIONS_H
#define POWER_SYSTEM_FUNCTIONS_H

struct power_system_data;

int power_system_init(char *filename, struct power_system_data **data);
void power_system_free(void);
double sequence_power_losses(int *sequence);

#endif //POWER_SYSTEM_FUNCTIONS_H
