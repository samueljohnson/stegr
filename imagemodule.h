int imagemod(char* file)
{
	printf("Loading image specific steg module.\n");
#define ThrowWandException(wand) \
{ \
  char \
    *description; \
 \
  ExceptionType \
    severity; \
 \
  description=MagickGetException(wand,&severity); \
  (void) fprintf(stderr,"%s %s %lu %s\n",GetMagickModule(),description); \
  description=(char *) MagickRelinquishMemory(description); \
  exit(-1); \
}

  MagickBooleanType
    status;

  MagickWand
    *magick_wand;

  //if (argc != 3)
    //{
      //(void) fprintf(stdout,"Usage: %s image thumbnail\n",argv[0]);
      //exit(0);
    //}
  /*
    Read an image.
  */
  MagickWandGenesis();
  char out[10];
  strcpy(out,"output.bmp");
  clock_t start;
  clock_t end;
  int time;
  start = clock();
  int width,height,blurfactor=2,imagequality=75;
  magick_wand=NewMagickWand();  
  status=MagickReadImage(magick_wand,file);
  width = MagickGetImageWidth(magick_wand);
  height = MagickGetImageHeight(magick_wand);
  printf("Dimensions of Original Image are : %d x %d \n",width,height);
  width=(width*19)/20;
  height=(height*19)/20;
  printf("Dimensions of Resized Image are : %d x %d \n",width,height);
  printf("Blur factor is %d\n",blurfactor);
  printf("Resize filter is Lanczos\n");
  printf("Image quality is %d percent\n",imagequality);
  printf("\nProcessing Image. Please Wait...\n");
  if (status == MagickFalse)
    ThrowWandException(magick_wand);

  MagickResetIterator(magick_wand);
  while (MagickNextImage(magick_wand) != MagickFalse)
    MagickResizeImage(magick_wand,width,height,LanczosFilter,blurfactor);
  MagickSetImageCompressionQuality(magick_wand,imagequality);
  /*
    Write the image then destroy it.
  */
  status=MagickWriteImages(magick_wand,out,MagickTrue);
  if (status == MagickFalse)
    ThrowWandException(magick_wand);
  magick_wand=DestroyMagickWand(magick_wand);
  MagickWandTerminus();
  printf("Done.\n");
  end = clock();
  /* Get time in milliseconds */
  time = (double)(end - start) / (CLOCKS_PER_SEC / 1000.0);
  printf("\nTime taken for processing : %d milliseconds\n",time);
  return(0);
}
