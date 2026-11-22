/* Real GTE command words for the DMPSX command macros of psyq/inline_c.h.
 *
 * psyq/inline_c.h (Psy-Q's DMPSX version 3 header, not in the repo) writes a placeholder `.word` per command that
 * Sony's DMPSX tool replaced after compiling; this header includes it and redefines each command macro with the
 * cop2 word DMPSX gives (the imm25 field holds Sony's command number in its top bits: rtps 0x4A180001, mvmva
 * 0x4A400012 + sf / mx / v / cv / lm). Checked against the retail code of every program (rtps, rtpt, nclip,
 * avsz3, avsz4, dpcs, dpct, gpf12 and the rtv0 / rtir mvmva forms occur there); the others follow the encoding.
 * Include this instead of psyq/inline_c.h (tools/install_c.py rewrites that include line).
 */
#ifndef GTE_H
#define GTE_H
#include "psyq/inline_c.h"

#define GTE_CMD(w) __asm__ volatile("nop;" "nop;" ".word " #w)

#undef gte_rtps
#define gte_rtps() GTE_CMD(0x4A180001)
#undef gte_rtpt
#define gte_rtpt() GTE_CMD(0x4A280030)
#undef gte_rt
#define gte_rt() GTE_CMD(0x4A480012)
#undef gte_rtv0
#define gte_rtv0() GTE_CMD(0x4A486012)
#undef gte_rtv1
#define gte_rtv1() GTE_CMD(0x4A48E012)
#undef gte_rtv2
#define gte_rtv2() GTE_CMD(0x4A496012)
#undef gte_rtir
#define gte_rtir() GTE_CMD(0x4A49E012)
#undef gte_rtir_sf0
#define gte_rtir_sf0() GTE_CMD(0x4A41E012)
#undef gte_rtv0tr
#define gte_rtv0tr() GTE_CMD(0x4A480012)
#undef gte_rtv1tr
#define gte_rtv1tr() GTE_CMD(0x4A488012)
#undef gte_rtv2tr
#define gte_rtv2tr() GTE_CMD(0x4A490012)
#undef gte_rtirtr
#define gte_rtirtr() GTE_CMD(0x4A498012)
#undef gte_rtv0bk
#define gte_rtv0bk() GTE_CMD(0x4A482012)
#undef gte_rtv1bk
#define gte_rtv1bk() GTE_CMD(0x4A48A012)
#undef gte_rtv2bk
#define gte_rtv2bk() GTE_CMD(0x4A492012)
#undef gte_rtirbk
#define gte_rtirbk() GTE_CMD(0x4A49A012)
#undef gte_ll
#define gte_ll() GTE_CMD(0x4A4A6412)
#undef gte_llv0
#define gte_llv0() GTE_CMD(0x4A4A6012)
#undef gte_llv1
#define gte_llv1() GTE_CMD(0x4A4AE012)
#undef gte_llv2
#define gte_llv2() GTE_CMD(0x4A4B6012)
#undef gte_llir
#define gte_llir() GTE_CMD(0x4A4BE012)
#undef gte_llv0tr
#define gte_llv0tr() GTE_CMD(0x4A4A0012)
#undef gte_llv1tr
#define gte_llv1tr() GTE_CMD(0x4A4A8012)
#undef gte_llv2tr
#define gte_llv2tr() GTE_CMD(0x4A4B0012)
#undef gte_llirtr
#define gte_llirtr() GTE_CMD(0x4A4B8012)
#undef gte_llv0bk
#define gte_llv0bk() GTE_CMD(0x4A4A2012)
#undef gte_llv1bk
#define gte_llv1bk() GTE_CMD(0x4A4AA012)
#undef gte_llv2bk
#define gte_llv2bk() GTE_CMD(0x4A4B2012)
#undef gte_llirbk
#define gte_llirbk() GTE_CMD(0x4A4BA012)
#undef gte_lc
#define gte_lc() GTE_CMD(0x4A4DA412)
#undef gte_lcv0
#define gte_lcv0() GTE_CMD(0x4A4C6012)
#undef gte_lcv1
#define gte_lcv1() GTE_CMD(0x4A4CE012)
#undef gte_lcv2
#define gte_lcv2() GTE_CMD(0x4A4D6012)
#undef gte_lcir
#define gte_lcir() GTE_CMD(0x4A4DE012)
#undef gte_lcv0tr
#define gte_lcv0tr() GTE_CMD(0x4A4C0012)
#undef gte_lcv1tr
#define gte_lcv1tr() GTE_CMD(0x4A4C8012)
#undef gte_lcv2tr
#define gte_lcv2tr() GTE_CMD(0x4A4D0012)
#undef gte_lcirtr
#define gte_lcirtr() GTE_CMD(0x4A4D8012)
#undef gte_lcv0bk
#define gte_lcv0bk() GTE_CMD(0x4A4C2012)
#undef gte_lcv1bk
#define gte_lcv1bk() GTE_CMD(0x4A4CA012)
#undef gte_lcv2bk
#define gte_lcv2bk() GTE_CMD(0x4A4D2012)
#undef gte_lcirbk
#define gte_lcirbk() GTE_CMD(0x4A4DA012)
#undef gte_dpcl
#define gte_dpcl() GTE_CMD(0x4A680029)
#undef gte_dpcs
#define gte_dpcs() GTE_CMD(0x4A780010)
#undef gte_dpct
#define gte_dpct() GTE_CMD(0x4AF8002A)
#undef gte_intpl
#define gte_intpl() GTE_CMD(0x4A980011)
#undef gte_sqr12
#define gte_sqr12() GTE_CMD(0x4AA80428)
#undef gte_sqr0
#define gte_sqr0() GTE_CMD(0x4AA00428)
#undef gte_ncs
#define gte_ncs() GTE_CMD(0x4AC8041E)
#undef gte_nct
#define gte_nct() GTE_CMD(0x4AD80420)
#undef gte_ncds
#define gte_ncds() GTE_CMD(0x4AE80413)
#undef gte_ncdt
#define gte_ncdt() GTE_CMD(0x4AF80416)
#undef gte_nccs
#define gte_nccs() GTE_CMD(0x4B08041B)
#undef gte_ncct
#define gte_ncct() GTE_CMD(0x4B18043F)
#undef gte_cdp
#define gte_cdp() GTE_CMD(0x4B280414)
#undef gte_cc
#define gte_cc() GTE_CMD(0x4B38041C)
#undef gte_nclip
#define gte_nclip() GTE_CMD(0x4B400006)
#undef gte_avsz3
#define gte_avsz3() GTE_CMD(0x4B58002D)
#undef gte_avsz4
#define gte_avsz4() GTE_CMD(0x4B68002E)
#undef gte_op12
#define gte_op12() GTE_CMD(0x4B78000C)
#undef gte_op0
#define gte_op0() GTE_CMD(0x4B70000C)
#undef gte_gpf12
#define gte_gpf12() GTE_CMD(0x4B98003D)
#undef gte_gpf0
#define gte_gpf0() GTE_CMD(0x4B90003D)
#undef gte_gpl12
#define gte_gpl12() GTE_CMD(0x4BA8003E)
#undef gte_gpl0
#define gte_gpl0() GTE_CMD(0x4BA0003E)

#endif
