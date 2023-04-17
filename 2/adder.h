#ifndef _ADDER_H_
#define _ADDER_H_

#include <iostream>
using namespace std;

#include <systemc>
using namespace sc_dt;
using namespace sc_core;

const int WIDTH = 4;

class adder : public sc_module {
public:
  sc_in_clk i_clk;
  sc_in<bool> i_rst;
  sc_fifo_in<sc_ufixed_fast<WIDTH> > i_a_port;
  sc_fifo_in<sc_ufixed_fast<WIDTH> > i_b_port;
  sc_fifo_out<sc_ufixed_fast<WIDTH+1> > o_sum_port;

  void do_add() {
    float h = [1/2,1/3,1/6];
    float in_temp[128];
     
    /*
    while (true) {
        _i_a = i_a_port.read();
        _i_b = i_b_port.read();
        wait();
        _o_sum = _i_a + _i_b;
        o_sum_port.write(_o_sum);
        wait();
    }
*/
    for(int aaa = 0; aaa<128;aaa++){
      in_temp[aaa] = i_a_port.read();
      wait();
    }
    for(int n=0;n<64;n++)
    {
      _o_sum = 0;
      for(int k=0;k<3<k++)
      {
        if(n*2-k+1<0) {
          _o_sum = 0 + _o_sum;
          wait();
        }
        else{
          _o_sum = h[k]*in_temp[n*2-k+1] + _o_sum;
          wait();
        }

      }
      o_sum_port.write(_o_sum);
    }
  }

  SC_HAS_PROCESS(adder);
  adder(sc_module_name name, int i) : id(i) { 
    SC_THREAD(do_add);  
    sensitive << i_clk.pos();
    dont_initialize();
  }

  sc_ufixed_fast<WIDTH> i_a() { return _i_a; }
  sc_ufixed_fast<WIDTH> i_b() { return _i_b; }
  sc_ufixed_fast<WIDTH> o_sum() { return _o_sum; }

private:
  const int id;
  sc_ufixed_fast<WIDTH> _i_a;
  sc_ufixed_fast<WIDTH> _i_b;
  sc_ufixed_fast<WIDTH+1> _o_sum;

 
};

#endif
