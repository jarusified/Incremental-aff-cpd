import glob
from distutils.core import setup
import platform

if len(glob.glob('ipca_aff_cpd_cpp*.so')) == 0:
    raise ValueError(
        'ipca_aff_cpd_cpp*.so is not found. You have not finished \
        compiling related cpp hpp files or \'python3-config --extension-suffix\'\
        command does not work properly in your environment')
ipca_aff_cpd_so = glob.glob('ipca_aff_cpd_cpp*.so')[0]

setup(
    name='ipca_aff_cpd',
    version=0.1,
    packages=[''],
    package_dir={'': '.'},
    package_data={'': [ipca_aff_cpd_so]},
    py_modules=['ipca_aff_cpd_cpp', 'ipca_aff_cpd'])
