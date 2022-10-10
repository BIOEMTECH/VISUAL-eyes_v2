import os 
import cv2  
from PIL import Image
import numpy as np
import argparse

parser = argparse.ArgumentParser(description='Invert Xray image')
parser.add_argument('-i', type=str, required=True, help='input Xray image path')
args = parser.parse_args()

minimum =115
maximum = 255
contr_factor = 1.0
bright_factor = 0

xray_filepath=args.i
input_xray = Image.open(xray_filepath)
np_array = np.array(input_xray.convert('L'))
inverted_array=np.invert(np_array)

inverted_xray = np.clip(contr_factor*inverted_array + bright_factor, minimum, maximum)
inverted_xray = np.int_((inverted_xray - minimum)*255/(maximum-minimum))

cv2.imwrite(xray_filepath,inverted_xray)