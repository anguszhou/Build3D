# Script for preparing images and calibration data 
#   for Yasutaka Furukawa's PMVS system

# Apply radial undistortion to the images
RadialUndistort c:\Zhcong\MyGit\Build3D\Build3DProject\list.txt  c:\Zhcong\MyGit\Build3D\Build3DProject\bundle\bundle.out 

# Create directory structure
mkdir -p pmvs/
mkdir -p pmvs/txt/
mkdir -p pmvs/visualize/
mkdir -p pmvs/models/

# Copy and rename files
cp C:\Zhcong\MyGit\Build3D\Build3DProject\examples\cambridge\0000.rd.jpg pmvs/visualize/0000.jpg
mv 0000.txt pmvs/txt/
cp C:\Zhcong\MyGit\Build3D\Build3DProject\examples\cambridge\0001.rd.jpg pmvs/visualize/0001.jpg
mv 0001.txt pmvs/txt/
cp C:\Zhcong\MyGit\Build3D\Build3DProject\examples\cambridge\0002.rd.jpg pmvs/visualize/0002.jpg
mv 0002.txt pmvs/txt/
cp C:\Zhcong\MyGit\Build3D\Build3DProject\examples\cambridge\0003.rd.jpg pmvs/visualize/0003.jpg
mv 0003.txt pmvs/txt/
cp C:\Zhcong\MyGit\Build3D\Build3DProject\examples\cambridge\0004.rd.jpg pmvs/visualize/0004.jpg
mv 0004.txt pmvs/txt/
cp C:\Zhcong\MyGit\Build3D\Build3DProject\examples\cambridge\0005.rd.jpg pmvs/visualize/0005.jpg
mv 0005.txt pmvs/txt/
cp C:\Zhcong\MyGit\Build3D\Build3DProject\examples\cambridge\0006.rd.jpg pmvs/visualize/0006.jpg
mv 0006.txt pmvs/txt/
cp C:\Zhcong\MyGit\Build3D\Build3DProject\examples\cambridge\0007.rd.jpg pmvs/visualize/0007.jpg
mv 0007.txt pmvs/txt/
cp C:\Zhcong\MyGit\Build3D\Build3DProject\examples\cambridge\0008.rd.jpg pmvs/visualize/0008.jpg
mv 0008.txt pmvs/txt/
cp C:\Zhcong\MyGit\Build3D\Build3DProject\examples\cambridge\0009.rd.jpg pmvs/visualize/0009.jpg
mv 0009.txt pmvs/txt/
cp C:\Zhcong\MyGit\Build3D\Build3DProject\examples\cambridge\0010.rd.jpg pmvs/visualize/0010.jpg
mv 0010.txt pmvs/txt/
cp C:\Zhcong\MyGit\Build3D\Build3DProject\examples\cambridge\0011.rd.jpg pmvs/visualize/0011.jpg
mv 0011.txt pmvs/txt/
cp C:\Zhcong\MyGit\Build3D\Build3DProject\examples\cambridge\0012.rd.jpg pmvs/visualize/0012.jpg
mv 0012.txt pmvs/txt/
cp C:\Zhcong\MyGit\Build3D\Build3DProject\examples\cambridge\0013.rd.jpg pmvs/visualize/0013.jpg
mv 0013.txt pmvs/txt/
cp C:\Zhcong\MyGit\Build3D\Build3DProject\examples\cambridge\0014.rd.jpg pmvs/visualize/0014.jpg
mv 0014.txt pmvs/txt/
cp C:\Zhcong\MyGit\Build3D\Build3DProject\examples\cambridge\0015.rd.jpg pmvs/visualize/0015.jpg
mv 0015.txt pmvs/txt/
cp C:\Zhcong\MyGit\Build3D\Build3DProject\examples\cambridge\0016.rd.jpg pmvs/visualize/0016.jpg
mv 0016.txt pmvs/txt/
cp C:\Zhcong\MyGit\Build3D\Build3DProject\examples\cambridge\0017.rd.jpg pmvs/visualize/0017.jpg
mv 0017.txt pmvs/txt/
cp C:\Zhcong\MyGit\Build3D\Build3DProject\examples\cambridge\0018.rd.jpg pmvs/visualize/0018.jpg
mv 0018.txt pmvs/txt/
cp C:\Zhcong\MyGit\Build3D\Build3DProject\examples\cambridge\0019.rd.jpg pmvs/visualize/0019.jpg
mv 0019.txt pmvs/txt/
cp C:\Zhcong\MyGit\Build3D\Build3DProject\examples\cambridge\0020.rd.jpg pmvs/visualize/0020.jpg
mv 0020.txt pmvs/txt/
cp C:\Zhcong\MyGit\Build3D\Build3DProject\examples\cambridge\0021.rd.jpg pmvs/visualize/0021.jpg
mv 0021.txt pmvs/txt/
cp C:\Zhcong\MyGit\Build3D\Build3DProject\examples\cambridge\0022.rd.jpg pmvs/visualize/0022.jpg
mv 0022.txt pmvs/txt/
cp C:\Zhcong\MyGit\Build3D\Build3DProject\examples\cambridge\0023.rd.jpg pmvs/visualize/0023.jpg
mv 0023.txt pmvs/txt/
cp C:\Zhcong\MyGit\Build3D\Build3DProject\examples\cambridge\0024.rd.jpg pmvs/visualize/0024.jpg
mv 0024.txt pmvs/txt/
cp C:\Zhcong\MyGit\Build3D\Build3DProject\examples\cambridge\0028.rd.jpg pmvs/visualize/0025.jpg
mv 0025.txt pmvs/txt/

# Sample commands for running pmvs:
#   affine 26 pmvs/ 4
#   match 26 pmvs/ 2 0 0 1 0.7 5
