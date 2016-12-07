#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "cache.h"
#include "memory.h"

using namespace std;


const int size =  32 * KB;               //输入以byte为单位
const int block = 128;
const int associativity = 1;


char * PATH;

void trace(Cache* level1)
{  

    FILE*fp=fopen(PATH,"r");
    char b;
    long int addr;
    // fscanf(fp,"%c\t%lu\n",&b,&addr);
    // cout<<b<<addr;
    
    while(!feof(fp)){
        fscanf(fp,"%c\t%lu\n",&b,&addr);
        /* if(!(isdigit(addr)))
         {
         cout<<"Wrong address!"<<endl;
         return;
         }*/
     
        /*if(addr>(1<<63))   //若地址超过64位uint
        {
            cout<<"Address Overstack!"<<endl;
            return;
        }*/
        
        bool r_or_w;
        if(b == 'r')
            r_or_w = 1;
        else if(b == 'w')
            r_or_w = 0;
        else
        {
            cout<<"Wrong operation!"<<endl; //若操作不是r or w
            return;
        }

        int visit_len = 1;  // 我们先假设我们访问缓存时的数据大小总是小于block的大小
        level1->visit(addr, visit_len, r_or_w);
   
  }

  fclose(fp);    //  Maybe wrong
}
//LRU实现：给每个line结构体维护一个lastvisittime（long_int）
//用constant写读入的参数；


int main(int argc, char  *argv[]) 
{

    PATH = argv[1];
    /****Initialization Aruguments****/

    Memory* mem = new Memory();

    StorageStats stats;

    StorageLatency mem_latency;
    mem_latency.bus_latency = 6;
    mem_latency.hit_latency = 100;


    StorageLatency lv1_lentency;
    lv1_lentency.bus_latency = 0;
    lv1_lentency.hit_latency = 8;

    


    /*************************/

    //*****Simulator's code****/
    

    Cache*  lv1_cache = new Cache(size, block, associativity, WRITE_BACK_ALLOCATE, LRU);    
    lv1_cache->SetLower(mem);

    lv1_cache->SetStats(stats);
    lv1_cache->SetLatency(lv1_lentency);

    mem->SetStats(stats);
    mem->SetLatency(mem_latency);


    trace(lv1_cache);


    //任何时刻，总访问时间由各个Storage 的 Stats.access_time 之和组成
    //但是只考察cache的命中情况

    StorageStats res_lv1_stats, res_mem_stats;
    lv1_cache->GetStats(res_lv1_stats);
    mem->GetStats(res_mem_stats);
    printf("\naccess_counter = %d\nmiss_num= %d\n\
            \naccess_time = %d\nmiss_rate:  %f\n\
            \nreplace_num = %d\naccess_lower_num = %d\n"
            , res_lv1_stats.access_counter, res_lv1_stats.miss_num
            , res_lv1_stats.access_time + res_mem_stats.access_time
            , (double(res_lv1_stats.miss_num)/double(res_lv1_stats.access_counter))
            , res_lv1_stats.replace_num, res_lv1_stats.access_lower_num);

        printf("\nMem access_counter = %d\n\
            \nMem access time = %d\n"
            , res_mem_stats.access_counter
            , res_mem_stats.access_time);
    // /*************************/


    return 0;
}
  
