# image-manipulation

Convert .PNG image to jpeg format, with cutomizable background Colour<br>
Convert .webp image to .PNG format (quality and colour will not take effect)<br>
Converts better than GIMP with background Colour<br>

# use
arg<1>: input image fileName<br>
arg[2]: output fileName (default .jpg)<br>
arg[3]: output quality  (default 100) unused for .PNG<br>
arg[4]: RGB r (0-255)<br>
arg[5]: RGB g (0-255)<br>
arg[6]: RGB b (0-255)<br>

ConvertImage.exe 1.png "90Q black.jpg" 90
ConvertImage.exe 1.webp "png.png"

ps. Does not Accept UTF fileNames

# test the Program
the file "1.png" is provided solely for User testing purposes of The Program, it is not to be connected with The Program itself or its Source.

# GNU General Public License
see the <a href="src/License.txt">src/License.txt</a>
