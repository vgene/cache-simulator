/*------------------------------------------------------------
 *                              CACTI 5.3
 *         Copyright 2008 Hewlett-Packard Development Corporation
 *                         All Rights Reserved
 *
 * Permission to use, copy, and modify this software and its documentation is
 * hereby granted only under the following terms and conditions.  Both the
 * above copyright notice and this permission notice must appear in all copies
 * of the software, derivative works or modified versions, and any portions
 * thereof, and both notices must appear in supporting documentation.
 *
 * Users of this software agree to the terms and conditions set forth herein, and
 * hereby grant back to Hewlett-Packard Company and its affiliated companies ("HP")
 * a non-exclusive, unrestricted, royalty-free right and license under any changes, 
 * enhancements or extensions  made to the core functions of the software, including 
 * but not limited to those affording compatibility with other hardware or software
 * environments, but excluding applications which incorporate this software.
 * Users further agree to use their best efforts to return to HP any such changes,
 * enhancements or extensions that they make and inform HP of noteworthy uses of
 * this software.  Correspondence should be provided to HP at:
 *
 *                       Director of Intellectual Property Licensing
 *                       Office of Strategy and Technology
 *                       Hewlett-Packard Company
 *                       1501 Page Mill Road
 *                       Palo Alto, California  94304
 *
 * This software may be distributed (but not offered for sale or transferred
 * for compensation) to third parties, provided such third parties agree to
 * abide by the terms and conditions of this notice.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND HP DISCLAIMS ALL
 * WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS.   IN NO EVENT SHALL HP 
 * CORPORATION BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 * DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 * PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS
 * ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
 * SOFTWARE.
 *------------------------------------------------------------*/

#include "io.h"
#include <iostream>
#include <cmath>
using namespace std;


int main(int argc,char *argv[])
{
  final_results result2;

  if (argc != 4)
  {
    cout << "The number of arguments must be 3 (cache size, block size, associativity) -- please refer to README file" << endl;
    exit(1);
  }
  else
  {
    result2 = cacti_interface(atoi(argv[1]),
                              atoi(argv[2]),
                              atoi(argv[3]),
                              1,
                              0,
                              0,
                              0,
                              1,
                              65,
                              512,
                              0,
                              0,
                              0,
                              1,
                              0,
                              0,
                              0,
                              0,
                              1,
                              300,
                              0,
                              0,
                              0,
                              0,
                              1,
                              1,
                              1,
                              1,
                              0,
                              0,
                              50,
                              10,
                              10,
                              0,
                              1,
                              1);
  }

	 
  int cycle;
  cycle = ceil(2000000000*result2.access_time); 
  cout << result2.access_time<<" "<< cycle<< endl;
  return 0;
}
