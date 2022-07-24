07/23/22
Error was found in the translationg and aspect ratio function.
specifcally
double translationY = (((double) Image->getHeight() - y_height) / 2.0);
double translationX = (((double)Image ->getWidth() - x_width)/ 2.0);
was missing a parenthesis around the numerator