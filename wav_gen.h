#pragma once

enum WavWave
{
  WavSinus=0,
  WavTriangle,
  WavSquare,
  
};

/**
 */
class WavGenerator
{
public:
                    WavGenerator(int csPin);
            void    setWaveForm(WavWave wave);
            void    setFrequency(float fq);

  
protected:  
            AD9833  _gen;  
            int     _cs;
};