#include"System.h"

#include <stdio.h>
#include <memory>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <pthread.h>
#include <iostream>

namespace emcache
{

    namespace
    {

        pid_t gettid()
        {
#if defined(__APPLE__)
            uint64_t tid64;
            pthread_threadid_np(NULL, &tid64);
            //std::cout << "tid64:" << tid64 << std::endl;
            return (pid_t)tid64;
#else
            return static_cast<pid_t>(::syscall(SYS_gettid));
#endif
        }

    }  // namespace


    // typedef struct CPU_PACKED         //定义一个cpu occupy的结构体
    // {
    // char name[20];             //定义一个char类型的数组名name有20个元素
    // unsigned int user;        //定义一个无符号的int类型的user
    // unsigned int nice;        //定义一个无符号的int类型的nice
    // unsigned int system;    //定义一个无符号的int类型的system
    // unsigned int idle;         //定义一个无符号的int类型的idle
    // unsigned int iowait;
    // unsigned int irq;
    // unsigned int softirq;
    // }CPU_OCCUPY;


    // struct MemProcInfo       //定义一个mem occupy的结构体
    // {
    //     char name[20];      //定义一个char类型的数组名name有20个元素
    //     unsigned long mem;
    //     char name02[20];
    // };


    // struct MemInfo         //定义一个mem occupy的结构体
    // {
    //     double mem_total;
    //     double mem_used_rate;
    // };


    // typedef struct DEV_MEM         //定义一个mem occupy的结构体
    // {
    //         double total,used_rate;
    // }DEV_MEM;
    __thread int t_cachedTid = 0;
    __thread char t_tidString[32];
    __thread int t_tidStringLength = 6;
    __thread const char *t_threadName = "unknown";


    void CacheTid()
    {
        if (t_cachedTid == 0)
        {
            t_cachedTid = gettid();
            //std::cout << "tid:" << t_cachedTid << std::endl;
            t_tidStringLength = snprintf(t_tidString, sizeof(t_tidString), "%5d ", t_cachedTid);
        }
    }

    bool IsMainThread()
    {
        return Tid() == ::getpid();
    }

    MemInfo GetMemoccupy()    // get RAM message
    {

        char buff[256];
        MemProcInfo m;
        MemInfo result;

        double memTotal = 0;
        // double memFree = 0;
        double memAvailable = 0;

        FILE *fd = fopen ("/proc/meminfo", "r");

        // memTotal
        fgets (buff, sizeof(buff), fd);
        sscanf (buff, "%s %lu %s\n", m.name, &m.mem, m.name02);
        memTotal = m.mem;

        // memFree
        // fgets (buff, sizeof(buff), fd);
        // sscanf (buff, "%s %lu %s\n", m.name, &m.mem, m.name02);
        // memFree = m.mem;

        // memAvailable
        fgets (buff, sizeof(buff), fd);
        sscanf (buff, "%s %lu %s\n", m.name, &m.mem, m.name02);
        memAvailable = m.mem;

        result.mem_used_rate = (memTotal - memAvailable) / memTotal;
        result.mem_total = memTotal / 1024;

        fclose(fd);     //关闭文件fd
        return result;
    }

    bool MemoryIsLow()
    {
    #if !defined(__APPLE__)
        MemInfo  memInfo = GetMemoccupy();
        if (memInfo.mem_used_rate >= Mem_Used_Rate)
        {
            std::cout << "Mem return true" << std::endl;
            return true;
        }
    #endif
        std::cout << "Mem return flase" << std::endl;

        return false;
    }




    // double cal_cpuoccupy (CPU_OCCUPY *o, CPU_OCCUPY *n)
    // {
    //     double od, nd;
    //     double id, sd;
    //     double cpu_use ;

    //     od = (double) (o->user + o->nice + o->system +o->idle+o->softirq+o->iowait+o->irq);//第一次(用户+优先级+系统+空闲)的时间再赋给od
    //     nd = (double) (n->user + n->nice + n->system +n->idle+n->softirq+n->iowait+n->irq);//第二次(用户+优先级+系统+空闲)的时间再赋给od

    //     id = (double) (n->idle);    //用户第一次和第二次的时间之差再赋给id
    //     sd = (double) (o->idle) ;    //系统第一次和第二次的时间之差再赋给sd
    //     if((nd-od) != 0)
    //     cpu_use =100.0- ((id-sd))/(nd-od)*100.00; //((用户+系统)乖100)除(第一次和第二次的时间差)再赋给g_cpu_used
    //     else cpu_use = 0;
    //     return cpu_use;
    // }

    // void get_cpuoccupy (CPU_OCCUPY *cpust)
    // {
    //     FILE *fd;
    //     int n;
    //     char buff[256];
    //     CPU_OCCUPY *cpu_occupy;
    //     cpu_occupy=cpust;

    //     fd = fopen ("/proc/stat", "r");
    //     fgets (buff, sizeof(buff), fd);

    //     sscanf (buff, "%s %u %u %u %u %u %u %u", cpu_occupy->name, &cpu_occupy->user, &cpu_occupy->nice,&cpu_occupy->system, &cpu_occupy->idle ,&cpu_occupy->iowait,&cpu_occupy->irq,&cpu_occupy->softirq);

    //     fclose(fd);
    // }

    // double getCpuRate()
    // {
    //     CPU_OCCUPY cpu_stat1;
    //     CPU_OCCUPY cpu_stat2;
    //     double cpu;
    //     get_cpuoccupy((CPU_OCCUPY *)&cpu_stat1);
    //     sleep(1);

    //     //第二次获取cpu使用情况
    //     get_cpuoccupy((CPU_OCCUPY *)&cpu_stat2);

    //     //计算cpu使用率
    //     cpu = cal_cpuoccupy ((CPU_OCCUPY *)&cpu_stat1, (CPU_OCCUPY *)&cpu_stat2);

    //     return cpu;
    // }


    // DEV_MEM *get_devmem()        // get hard disk meeeage
    // {
    //         FILE * fp;
    //         int h=0;
    //         char buffer[80],a[80],d[80],e[80],f[80],buf[256];
    //         double c,b;
    //         fp=popen("df","r");
    //         fgets(buf,256,fp);
    //         double dev_total=0,dev_used=0;
    //         DEV_MEM  *dev=(DEV_MEM *)malloc(sizeof(DEV_MEM));
    //         while(6==fscanf(fp,"%s %lf %lf %s %s %s",a,&b,&c,d,e,f))
    //         {
    //                 dev_total+=b;
    //                 dev_used+=c;
    //         }
    //         dev->total=dev_total/1024/1024;;
    //         dev->used_rate=dev_used/dev_total*100;
    //         pclose(fp);
    //         return dev;
    // }

} //namespace emcache
