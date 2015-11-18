/***************************************************************************
 *   Copyright (C) 2015 by Author: e1100983   *
 *     *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

/*********************************************************************
 *
 * 1.  NAME
 *     tcpip.c
 * 2.  DESCRIPTION
 *
 * 6.  VERSIONS
 *       Original:
 *         11.11.2015
 *
 *       Version history: Veni , Vidi , Vici
 *        
 *
 **********************************************************************/

/*-------------------------------------------------------------------*
 *    HEADER FILES                                                    *
 *--------------------------------------------------------------------*/
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>

#define BUFFSIZE 32
void Die(char *mess) { perror(mess); exit(1); }

/*-------------------------------------------------------------------*
 *    GLOBAL VARIABLES                                                *
 *--------------------------------------------------------------------*/
/* Control flags */

/* Globaal constants */

/* Globaal variables */

/* Globaal structures */

/*-------------------------------------------------------------------*
 *    FUNCTION PROTOTYPES                                             *
 *--------------------------------------------------------------------*/

/*********************************************************************
 *    MAIN PROGRAM                                                      *
 **********************************************************************/

int main(int argc, char *argv[])
{
  int sock;
  struct sockaddr_in echoserver;
  char buffer[BUFFSIZE];
  unsigned int echolen;
  int received = 0;
  
  if (argc != 4)
  {
    fprintf(stderr, "USAGE: TCPecho <server_ip> <word> <port>\n");
    exit(1);
  }
  /* Create the TCP socket */
  if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
  {
    Die("Failed to create socket");
  }
}

/*********************************************************************
 *    FUNCTIONS                                                     *
 **********************************************************************/

/*********************************************************************
 ;	F U N C T I O N    D E S C R I P T I O N
 ;---------------------------------------------------------------------
 ; NAME:
 ; DESCRIPTION:
 ;	Input:
 ;	Output:
 ;  Used global variables:
 ; REMARKS when using this function:
 ;*********************************************************************/
