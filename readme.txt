Instructions: 

Available Functions:
    flipImage, flipColorImage, multColor, addColor, scaleUp, multiRoi, thresholdG (the new function), addG, binarizeG
    
Default parameters:
    The parameters are set up to output all three tasks in their respective folders for convenience.
    If you decide to output a file to a different folder, the folder must already exist for the save_image() function to work

Configuring the parameters file: 
    The parameter file is able to ignore comment lines starting with "#" and empty lines.
    Each line corresponds to a different set of parameters for a function and a new line separates the functions
    
Building and executing:
    using Visual Studio Code, you can build and run the main.cpp by opening the command pallete
    and running the task, "C++ build and run main.cpp". Make sure that you are looking at main.cpp when you
    decide to run the task.


Specific function formatting:
    multiRoi: "input output multiRoi func1 rX1 rY1 rSize1 func2 rX2 rY2 rSize2 func3 rX3 rY3 rSize3
        This function supports 1-3 Rois and only supports the thresholdG, addG, and binarizeG functions. 
        *If you want to run thresholdG, addG, and binarizeG separately with different parameters without recompiling, then you can do so without multiRoi
        Because of the multiRoi format, separate parameters for these functions can only be modified by changing the appropriate macros and 
        recompiling the program.
        These macros can be found at runFromParameters.cpp:
            ADD_G_VAL
            BINARIZE_G_VAL
            THRESHOLD_G_T
            THRESHOLD_G_V

    * You can string greyRoi and colorRoi with other functions on a different line
    greyRoi: "input output greyRoi rX rY rS"
        Makes a greyscale roi image from a greyscale image
        
    colorRoi: "input output colorRoi rX rY rS"
        Makes a color roi image from a color image


    flipImage: "input output flipImage degree1 degree2"
        This function only works with greyScale images. It produces 3 images: 
            1. an image that is flipped, 
            2. rotated by multiple of 90 (given by degree1), 
            3. another rotated by a multiple of 90 (given by degree2)

    flipColorImage: "input output flipColorImage degree1 degree2"
        This function works with color images. Its functionality is the same as flipImage

    multColor: "input output multColor moreC" 
        This function works with color images. It multiplies every channel of color by moreC

    addColor: "input output addColor moreC" 
        This function works with color images. It adds to every channel of color by moreC

    scaleUp: "input output scaleUp scaleFactor rX rY rSize"
        This function scales up the image by scaleFactor.
        If you want to respect the original size of the source image, then have rX=0, rY=0, rSize="the size of the source file"
    
    thresholdG, binarizeG, and addG: "input output funcName param(s) rX rY rSize"
        These functions have a similar format. For thresholdG, remember that there are two params, T and V, respectively in that order
