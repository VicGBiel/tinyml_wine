#ifndef WINE_NORM_H
#define WINE_NORM_H

// Valores copiados da Célula 9 do seu Notebook (scaler.mean_ e scaler.scale_)
static const float wine_means[13] = {
    12.9715, 2.3400, 2.3649, 19.6254, 
    99.6338, 2.2737, 1.9854, 0.3601, 
    1.6002, 4.9896, 0.9490, 2.6062, 
    739.4789
};

static const float wine_stds[13] = {
    0.7997, 1.0974, 0.2674, 3.3689, 
    14.8848, 0.6193, 0.9486, 0.1188, 
    0.5777, 2.3267, 0.2258, 0.6872, 
    300.4355
};

#endif