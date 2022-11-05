#include "PulseProcSymbolData.h"


int32_t __not_in_flash_func(PulseProcSymbolData::advance)(
  InputStream *is,
  bool *pstate,
  PulseProc **top
) {
  if (_ns == 0)  {
    *pstate = !*pstate;
    return PP_COMPLETE;
  }
  if (_sb < _bps)  {
    int32_t r = is->readByte();
    DBG_PULSE("PulseProcSymbolData: data %ld\n", r);      
    if (r < 0) return PP_ERROR;    
    _sd = r | (_sd << 8);
    _sb += 8;
  }
  _sb -= _bps;
  uint32_t si = _sm & (_sd >> _sb);
  --_ns;
   _symbol->init(this, si);
  *top = _symbol;
  return PP_CONTINUE;
}

/*

int32_t __not_in_flash_func(PulseProcSymbolData::advance)(
  InputStream *is,
  bool *pstate,
  PulseProc **top
) {
  if (_ns == 0)  {
    *pstate = !*pstate;
    return PP_COMPLETE;
  }
  if (_sb < _bps)  {
    int32_t r = is->readByte();
    DBG_PULSE("PulseProcSymbolData: data %ld\n", r);      
    if (r < 0) return PP_ERROR;    
    _sd |= r << _sb;
    _sb += 8;
  }
  uint32_t si = _sm & _sd;
  _sd >>= _bps;
  _sb -= _bps;
  --_ns;
  _symbol->init(this, si);
  *top = _symbol;
  return PP_CONTINUE;
}

*/
