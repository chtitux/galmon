#pragma once
#include <string>
#include <stdio.h>
#include "navmon.hh"
#include <vector>
struct RTCMFrame
{
  std::string payload;
};

class RTCMReader
{
public:
  explicit RTCMReader(int fd) : d_fp(fdopen(fd, "r")) {}
  bool get(RTCMFrame& rf);
private:
  FILE* d_fp;
};


struct RTCMMessage
{
  void parse(const std::string& str);
  int type;
  int sow;
  int udi;
  bool mmi;
  bool reference;
  int ssrIOD, ssrProvider, ssrSolution;
  struct EphemerisDelta
  {
    SatID id;
    // in millimeters
    double radial, along, cross;
    double dradial, dalong, dcross;
    int iod;
  };
  struct ClockDelta
  {
    SatID id;
    double dclock0; // in meters
    double dclock1;
    double dclock2;
  };

  std::vector<EphemerisDelta> d_ephs;
  std::vector<ClockDelta> d_clocks;
  
};
