#  Because pybind11 cannot generate default parameters well, this code is to set them

import ipca_aff_cpd_cpp


class IPCAAFFCPD(ipca_aff_cpd_cpp.IPCAAFFCPD):
    """An extension version of the change point detection using adaptive
    forgetting factor with PCA for multivariate streaming data.

    Parameters
    ----------
    alpha: float, required
        The significance level. alpha should be set between 0 and 1.0.
        "Setting alpha is a simple matter of deciding on the width of the
        control limits, e.g. as in the construction of a confidence interval,
        alpha = 0.01 for a 99% interval. Clearly, larger values of alpha lead
        to narrower intervals and more sensitive detectors, resulting in an
        increase in false detections, etc." [Bodenham and Adams, 2017]
    eta: float, optional, (default=0.01)
        The step size (or learning rate). This parameter is not important for
        change detection based on [Bodenham and Adams, 2017]. Even if eta is
        changed, the quality of change detection will be similar. eta should be
        set between 0 and 1.0.
    burn_in_length: int, optional, (default=10)
        The length of burn-in period deciding the time window which will be
        used to estimate the parameters for the change point detection.
    inc_pca_forgetting_factor: float, optional, (default=1.0)
        The forgetting factor used for the incremental PCA (not for AFF based
        CPD).
        A forgetting factor, f,  provides a way to reduce the contributions of
        past observations to the latest result. The value of f ranges from 0 to
        1 where f = 1 means no past results will be forgotten. When 0 <= f < 1,
        the contributions of past observations gradually decrease as new data
        points are obtained. As described in [Ross et al., 2008], the effective
        size of the observation history (a number of observations which affect
        the PCA result) equals to m/(1 - f) (m: number of new data points). For
        example, when f = 0.98 and m = 2, the most recent 100 observations are
        effective.
    Attributes
    ----------
    Examples
    --------
    >>> import numpy as np
    >>> import pandas as pd
    >>> import matplotlib.pyplot as plt
    >>> from ipca_aff_cpd_cpp import IPCAAFFCPD

    >>> # load data
    >>> # df, x: row: data points (KPs), col: time points (time)
    >>> df = pd.read_csv('ross-df-256kp-500gvt_RbSec.csv')
    >>> X = np.array(df)
    >>> # dft, xt: row: time points (time), col: data points (KPs)
    >>> Xt = X.transpose()
    >>> dft = df.transpose()

    >>> # set up IPCAAFFCPD
    >>> alpha = 0.2
    >>> aff = IPCAAFFCPD(alpha=alpha)

    >>> # detect change points
    >>> change_points = []
    >>> for i in range(Xt.shape[0]):
    ...     change = aff.feed_predict(Xt[i, :])
    ...     if change:
    ...         print("Here is a change", i)
    ...         change_points.append(i)

    >>> # plot result
    >>> dft.plot.line(color="gray", linewidth=0.5, legend=False, alpha=0.5)
    >>> for change_point in change_points:
    ...     plt.axvline(x=change_point, color="#c74e52")
    >>> plt.show()

    Notes
    -----
    This algorithm combines the ideas from:
    `D. A. Bodenham and N. M. Adams, Continuous monitoring for changepoints in
    data streams using adaptive estimation, Statistics and Computing,
    vol. 27, no. 5, pp.1257--1270, 2017.`
    and
    `A. Qahtan, B. Alharbi, S. Wang, and X. Zhang, A PCA-Based Change Detection
    Framework for Multidimensional Data Streams, In Proc. ACM SIGKDD,
    pp.935--944, 2015.`
    References
    ----------
     D. A. Bodenham and N. M. Adams, Continuous monitoring for changepoints in
      data streams using adaptive estimation, Statistics and Computing,
      vol. 27, no. 5, pp.1257--1270, 2017.
     A. Qahtan, B. Alharbi, S. Wang, and X. Zhang, A PCA-Based Change Detection
      Framework for Multidimensional Data Streams, In Proc. ACM SIGKDD,
      pp.935--944, 2015.
    """

    def __init__(self,
                 alpha,
                 eta=0.01,
                 burn_in_length=10,
                 inc_pca_forgetting_factor=1.0):
        super().__init__(alpha, eta, burn_in_length, inc_pca_forgetting_factor)

    def feed(self, new_time_point):
        """Feed a new multivariate time point. This also updates the data,
        PCA result, etc. in the instance.

        Parameters
        ----------
        new_time_point : array-like, shape (1, n_features)
            A new time point to feed.
        Returns
        -------
        self: object
            Returns the instance itself.
        """
        return super().feed(new_time_point)

    def feed_with_pca_result_return(self,
                                    new_time_point,
                                    use_inc_pca=True,
                                    adjust_sign=True):
        """The same function with feed(), but this returns also a univariate
        value obtained after applying incremental PCA to the
        multivariate new time point.

        Parameters
        ----------
        new_time_point : array-like, shape (1, n_features)
            A new time point to feed.
        use_inc_pca : bool, optional (default: True)
            Whether using incremental PCA or not (for the paper writing purpose).
        adjust_sign : bool, optional (default: True)
            Whether using sign flip adjustment or not (for the paper writing purpose).
        Returns
        -------
        value_after_pca: float
            A univariate value obtained after applying incremental PCA to the
            multivariate new time point.
        """
        return super().feed_with_pca_result_return(new_time_point, use_inc_pca,
                                                   adjust_sign)

    def predict(self):
        """Return wheter the latest fed time point caused a change or not.

        Parameters
        ----------
        None
        Returns
        -------
        change : bool
            A change occured or not.
        """
        return super().predict()

    def feed_predict(self, new_time_point):
        """This function applies feed() then predict().

        Parameters
        ----------
        new_time_point : array-like, shape (1, n_features)
            A new time point to feed.
        Returns
        -------
        change : bool
            A change occured or not.
        """
        return super().feed_predict(new_time_point)
