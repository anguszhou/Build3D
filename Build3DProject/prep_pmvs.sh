# Script for preparing images and calibration data 
#   for Yasutaka Furukawa's PMVS system

# Apply radial undistortion to the images
RadialUndistort d:\Build3DProject\list.txt  d:\Build3DProject\bundle\bundle.out 

# Create directory structure
mkdir -p pmvs/
mkdir -p pmvs/txt/
mkdir -p pmvs/visualize/
mkdir -p pmvs/models/

# Copy and rename files
cp D:\Build3DProject\examples\pgm\img5.rd.jpg pmvs/visualize/0000.jpg
mv 0000.txt pmvs/txt/
cp D:\Build3DProject\examples\pgm\img5.rd.rd.jpg pmvs/visualize/0001.jpg
mv 0001.txt pmvs/txt/
cp D:\Build3DProject\examples\pgm\img6.rd.jpg pmvs/visualize/0002.jpg
mv 0002.txt pmvs/txt/
cp D:\Build3DProject\examples\pgm\img6.rd.rd.jpg pmvs/visualize/0003.jpg
mv 0003.txt pmvs/txt/

# Sample commands for running pmvs:
#   affine 4 pmvs/ 4
#   match 4 pmvs/ 2 0 0 1 0.7 5
