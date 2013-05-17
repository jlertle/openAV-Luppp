
#ifndef LUPPP_BUFFERS_H
#define LUPPP_BUFFERS_H

#include <cstring>
#include <jack/transport.h>

class Buffers
{
  public:
    Buffers()
    {
      memset( audio, 0, sizeof(float*)*2);
    }
    float* audio[2];
    
    enum BUFFER {
      MASTER_OUTPUT = 0,
      MASTER_INPUT,
    };
    
    // Jack details
    jack_nframes_t         nframes;
    jack_nframes_t         samplerate;
    
    jack_nframes_t          transportFrame;
    jack_position_t*        transportPosition;
    jack_transport_state_t* transportState;
    
};

#endif // LUPPP_BUFFERS_H
