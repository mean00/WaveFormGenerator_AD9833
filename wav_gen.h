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
            void    SetWaveForm(WavWave wave);
            void    SetFrequency(float fq);

  
protected:  
            AD9833  _gen;  
            int     _cs;
};