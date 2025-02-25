[![build maskbackgroundnoise](https://github.com/MouseSuite/maskbackgroundnoise/actions/workflows/build.yml/badge.svg)](https://github.com/MouseSuite/maskbackgroundnoise/actions/workflows/build.yml)

# maskbackgroundnoise
This tool peforms automated thresholding and mathematical morphology to identify the brain region in an *ex vivo* MRI where non-brain tissues have been physically removed prior to scanning.

## Copyright
Copyright (C) 2025 The Regents of the University of California.

## License
maskbackgroundnoise is licensed under [GNU Lesser General Public License v2.1 only](https://spdx.org/licenses/LGPL-2.1-only.html).

## Attribution
If you use maskbackgroundnoise in one of your research, please cite this repository.

## Documentation and Support
For more detailed information on maskbackgroundnoise, please visit our maskbackgroundnoise website, [https://mousesuite.org/maskbackgroundnoise/](https://mousesuite.org/maskbackgroundnoise/). 

You may also post comments or questions on our [MouseSuite discussion page](https://github.com/orgs/MouseSuite/discussions) or to our [issue tracker](https://github.com/MouseSuite/maskbackgroundnoise/issues).

## Usage
```
required settings:
-i <file>                      input file
-o <file>                      output file
--level <level>                level for threshold [0-1]

optional settings:
--license                      show the license information
-g                             debug
-v <level>                     verbosity [default: 0]
-m <mask_file>                 save initial threshold output
```
