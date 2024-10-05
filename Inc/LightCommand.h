#ifndef __LIGHTCOMMAND_H
#define __LIGHTCOMMAND_H

void run_lightCommand(void);
void validateCommand(void);
void lightCommand(void);
void handleInvalidCom(void);
void remoteModeMessage(void);
void localModeMessage(void);
void RON(void);
void ROFF(void);
void GON(void);
void GOFF(void);
void RFLASH(void);
void GFLASH(void);
void FLASHOFF(void);
void toggleflags(void);

#endif /* __LightCOMMAND_H */
