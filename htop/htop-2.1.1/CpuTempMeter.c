/*
htop - CpuTempMeter.c
(C) 2018 @lex
*/

#include "CpuTempMeter.h"
#include "Platform.h"
#include "CRT.h"

/*{
#include "Meter.h"
}*/

int CpuTempMeter_attributes[] = {
   CPU_TEMP
};

static void CpuTempMeter_setValues(Meter* this, char* buffer, int len) {
   int Temp;
   int bigLITTLE;
   int cluster;
   char buf_b[32];
   char buf_l[32];
   int ln = sizeof(buf_l);
   
   memset(buf_l, 0, sizeof(buf_l));
   memset(buf_b, 0, sizeof(buf_b));
   cluster = 0;
   
   bigLITTLE = Platform_getCpuBigLITTLE();
   if (bigLITTLE)  {
       Temp = Platform_getCpuTemp(cluster++);
       if (Temp > 1000) {
           Temp /= 1000;
       }
       xSnprintf(buf_b, ln, "%4d C", Temp);
       Temp = Platform_getCpuTemp(cluster);
       if (Temp > 1000) {
           Temp /= 1000;
       }
       xSnprintf(buf_l, ln, "%4d C", Temp);
       xSnprintf(buffer, len, "%s %s (big.LITTLE)", buf_b, buf_l);
       return;
   }
   Temp = Platform_getCpuTemp(cluster);
   if (Temp > 1000) {
       Temp /= 1000;
   }
   xSnprintf(buffer, len, "%4d C", Temp);
}

MeterClass CpuTempMeter_class = {
   .super = {
      .extends = Class(Meter),
      .delete = Meter_delete
   },
   .updateValues = CpuTempMeter_setValues, 
   .defaultMode = TEXT_METERMODE,
   .maxItems = 1,
   .total = 100.0,
   .attributes = CpuTempMeter_attributes,
   .name = "CpuTemp",
   .uiName = "CpuTemp",
   .caption = "Cpu Temp: "
};
