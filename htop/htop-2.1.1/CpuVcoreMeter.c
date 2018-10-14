/*
htop - CpuVcoreMeter.c
(C) 2018 @lex
*/

#include "CpuVcoreMeter.h"
#include "Platform.h"
#include "CRT.h"

/*{
#include "Meter.h"
}*/


int CpuVcoreMeter_attributes[] = {
   CPU_VCORE
};

static void CpuVcoreMeter_setValues(Meter* this, char* buffer, int len) {
   int v1,v2;
   int Vcore = Platform_getCpuVcore();
   if (Vcore > 1000) {
       Vcore /= 1000;
   }
   if (Vcore >= 1000) {
       Vcore /= 10;
       v1 = Vcore / 100;
       v2 = Vcore % 100;
       snprintf(buffer, len, "%d.%02d V", v1, v2);
   } else {
       snprintf(buffer, len, "%4d mV", Vcore);
   }
}

MeterClass CpuVcoreMeter_class = {
   .super = {
      .extends = Class(Meter),
      .delete = Meter_delete
   },
   .updateValues = CpuVcoreMeter_setValues, 
   .defaultMode = TEXT_METERMODE,
   .maxItems = 1,
   .total = 100.0,
   .attributes = CpuVcoreMeter_attributes,
   .name = "CpuVcore",
   .uiName = "CpuVcore",
   .caption = "Cpu Vcor: "
};
