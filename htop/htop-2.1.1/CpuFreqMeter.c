/*
htop - CpuFreqMeter.c
(C) 2018 @lex
*/

#include "CpuFreqMeter.h"
#include "Platform.h"
#include "CRT.h"

/*{
#include "Meter.h"
}*/


int CpuFreqMeter_attributes[] = {
   CPU_FREQ
};

static void CpuFreqMeter_setValues(Meter* this, char* buffer, int len) {
   int ghz,mhz,roundup;
   int cpu, Freq;
   int bigLITTLE;
   char buf[32];

   cpu = this->param;
   cpu--;
   if (cpu < 0) {
      // xSnprintf(buffer, len, "cpu: %d",cpu);
      cpu = 0;
   }
   bigLITTLE = Platform_getCpuBigLITTLE();
   if (bigLITTLE)  {
       if (bigLITTLE > 0) {
           if (cpu < bigLITTLE) {
               strcpy(buf, "(   .LITTLE)");
           } else {
               strcpy(buf, "(big.      )");
           }
       }
   }
   Freq = Platform_getCpuFreq(cpu);
   if (Freq > 1000) {
       Freq /= 1000;
   }
   if (Freq > 1000) {
       ghz = Freq / 1000;
       mhz = Freq % 1000;
       roundup = ((mhz % 10) > 5);
       mhz /= 10;
       mhz += roundup;
       if (bigLITTLE)  {
           xSnprintf(buffer, len, "%d.%02d GHz %s", ghz, mhz, buf);
       } else {
           xSnprintf(buffer, len, "%d.%02d GHz", ghz, mhz);
       }
   } else {
       if (bigLITTLE)  {
           xSnprintf(buffer, len, "%4d MHz %s", Freq, buf);
       } else {
            xSnprintf(buffer, len, "%4d MHz", Freq);
       }
   }
}

static void CpuFreqMeter_init(Meter* this) {
   int cpu = this->param;
   if (cpu > 0) {
       char caption[16];
       xSnprintf(caption, sizeof(caption), "CpuFreq%d: ", cpu);
       Meter_setCaption(this, caption);
    }
}

MeterClass CpuFreqMeter_class = {
   .super = {
      .extends = Class(Meter),
      .delete = Meter_delete
   },
   .updateValues = CpuFreqMeter_setValues, 
   .defaultMode = TEXT_METERMODE,
   .maxItems = 8,
   .total = 100.0,
   .attributes = CpuFreqMeter_attributes,
   .name = "CpuFreq",
   .uiName = "CpuFreq",
   .caption = "Cpu Freq: ",
   .init = CpuFreqMeter_init
};

static void AllCpuFreqMeter_init(Meter* this) {
   int cpus = this->pl->cpuCount;
   if (!this->drawData)
       this->drawData = xCalloc(cpus, sizeof(Meter*));
   Meter** meters = (Meter**) this->drawData;
   for (int i = 0; i < cpus; i++) {
        if (!meters[i])
             meters[i] = Meter_new(this->pl, i+1, (MeterClass*) Class(CpuFreqMeter));
        Meter_init(meters[i]);
   }
}

static void AllCpuFreqMeter_done(Meter* this) {
   int cpus = this->pl->cpuCount;
   Meter** meters = (Meter**) this->drawData;
   if (meters) {
       for (int i = 0; i < cpus; i++)
          Meter_delete((Object*)meters[i]);
  }
}


MeterClass AllCpuFreqMeter_class = {
   .super = {
      .extends = Class(Meter),
      .delete = Meter_delete
   },
   .updateValues = CpuFreqMeter_setValues, 
   .defaultMode = TEXT_METERMODE,
   .maxItems = 8,
   .total = 100.0,
   .attributes = CpuFreqMeter_attributes,
   .name = "AllCpuFreq",
   .uiName = "AllCpuFreq",
   .caption = "AllCpu Freq: ",
   .init = AllCpuFreqMeter_init,
   .done = AllCpuFreqMeter_done   
};

