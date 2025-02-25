// Copyright (C) 2025 The Regents of the University of California
//
// Created by David W. Shattuck, Ph.D.
//
// This file is part of maskbackgroundnoise.
//
// maskbackgroundnoise is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation, version 2.1.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
//

#include <vol3dsimple.h>
#include <volumeloader.h>
#include <thresholdtools.h>
#include <DS/morph32.h>
#include <DS/runlengthsegmenter.h>

template <class T>
T nthValue(const Vol3D<T> &vIn, size_t n)
{
  const auto ds=vIn.size();
  auto v=std::vector<T>(vIn.size());
  for (size_t i=0;i<ds;i++) v[i]=vIn[i];
  std::nth_element(v.begin(), v.begin()+n, v.end());
  return v[n];
}

int main(int argc, char *argv[])
{
  ArgParser ap("maskbackgroundnoise");
  ap.description="removes background noise by applying a threshold and performing mathematical morphology operations.";
  std::string mfname;
  float level=0.5f;
  ap.bind("m",mfname,"<mask_file>","save initial threshold output",false,false);
  ap.bind("-level",level,"<level>","level for threshold [0-1]",true,false);

  if (!ap.parseAndValidate(argc,argv)) return ap.usage();
  Vol3D<float32> vIn;
  if (!vIn.read(ap.ifname)) return CommonErrors::cantRead(ap.ifname);
  float f=nthValue(vIn,level*vIn.size());
  std::cout<<ap.ifname<<" : "<<f<<std::endl;
  Vol3D<uint8> vMask;
  vMask.makeCompatible(vIn);
  for (int i=0;i<vIn.size();i++) vMask[i] = (vIn[i]>f) ? 255 : 0;
  if (!mfname.empty())
    if (!vMask.write(mfname)) return CommonErrors::cantWrite(mfname);
  Vol3D<VBit> vBit;
  vBit.encode(vMask);
  Morph32 dmorph;
  RunLengthSegmenter rls;
  dmorph.erodeC(vBit);
  dmorph.erodeR(vBit);
  rls.segmentFG(vBit);
  dmorph.dilateC(vBit);
  dmorph.dilateR(vBit);
  dmorph.dilateC(vBit);
  dmorph.dilateR(vBit);
  dmorph.erodeC(vBit);
  dmorph.erodeR(vBit);
  rls.segmentBG(vBit);
  vBit.decode(vMask);
  if (!vMask.write(ap.ofname)) return CommonErrors::cantWrite(ap.ofname);
	return 0;
}
