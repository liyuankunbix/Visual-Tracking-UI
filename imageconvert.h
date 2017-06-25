#ifndef IMAGECONVERT_H
#define IMAGECONVERT_H

#include <QImage>
#include <opencv2/core.hpp>

cv::Mat QImageToMat(QImage image);
QImage MatToQImage(const cv::Mat& mat) ;
std::vector<std::string> readFileList(char *basePath);

#endif // IMAGECONVERT_H