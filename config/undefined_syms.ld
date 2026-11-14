/* Symbols outside the programs (hardware, scratchpad), shared by every link. */
/* Scratchpad variables (0x1F800000..0x1F8003FF) the matched C names; the retail code reaches them with lui/sb. */
D_1F80019B = 0x1F80019B;   /* cleared before a cooperative disc read */
D_1F8001F0 = 0x1F8001F0;   /* disc read: first sector */
D_1F8001F4 = 0x1F8001F4;   /* disc read: length in words */
D_1F8001F8 = 0x1F8001F8;   /* disc read: destination */
