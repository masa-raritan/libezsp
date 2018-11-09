/**
 * 
 */

#include "apsoption.h"


CAPSOption::CAPSOption()
{
  // default flags
  /** Include the destination EUI64 in the network frame. */
  dest_ieee = false;
  /** Send a ZDO request to discover the node ID of the destination, if it is not already know. */
  enable_addr_discovery = true;
  /** Causes a route discovery to be initiated if no route to the destination is known. */
  enable_route_discovery = true;
  /** Send the message using APS Encryption, using the Link Key shared with the destination node to encrypt the data at the APS Level. */
  encryption = false;
  /** Causes a route discovery to be initiated even if one is known. */
  force_route_discovery = false;
  /** This message is part of a fragmented message. This
    * option may only be set for unicasts. The groupId field
    * gives the index of this fragment in the low-order byte. If
    * the low-order byte is zero this is the first fragment and
    * the high-order byte contains the number of fragments in
    * the message.
  */
  fragment = false;
  /** Resend the message using the APS retry mechanism. */
  retry = true;
  /** Include the source EUI64 in the network frame. */
  src_ieee = true;
  /** This incoming message is a ZDO request not handled by
    * the EmberZNet stack, and the application is responsible
    * for sending a ZDO response. This flag is used only when
    * the ZDO is configured to have requests handled by the
    * application. See the
    * EZSP_CONFIG_APPLICATION_ZDO_FLAGS configuration
    * parameter for more information.
  */
  zdo_rsp_requiered = false;
}

uint16_t CAPSOption::GetEmberApsOption(void)
{
  uint16_t lo_option;

  lo_option = ((encryption<<5)&0x0020);
  lo_option |= ((retry<<6)&0x0040);
  lo_option |= ((enable_route_discovery<<8)&0x0100);
  lo_option |= ((force_route_discovery<<9)&0x0200);
  lo_option |= ((src_ieee<<10)&0x0400);
  lo_option |= ((dest_ieee<<11)&0x0800);
  lo_option |= ((enable_addr_discovery<<12)&0x1000);
  lo_option |= ((zdo_rsp_requiered<<14)&0x4000);
  lo_option |= ((fragment<<15)&0x8000);

  return lo_option;
}

void CAPSOption::SetEmberApsOption( uint16_t i_option )
{
  encryption = (0!=(i_option&0x0020));
  retry = (0!=(i_option&0x0040));
  enable_route_discovery = (0!=(i_option&0x0100));
  force_route_discovery = (0!=(i_option&0x0200));
  src_ieee = (0!=(i_option&0x0400));
  dest_ieee = (0!=(i_option&0x0800));
  enable_addr_discovery = (0!=(i_option&0x1000));
  zdo_rsp_requiered = (0!=(i_option&0x4000));
  fragment = (0!=(i_option&0x8000));
}

