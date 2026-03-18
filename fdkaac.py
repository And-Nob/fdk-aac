import shutil
import os

def setup(py_params_dict):
    attributes_dict = {
        "version": "0.1",
        "generate_hw": False,
    }

    # Don't copy files for other targets (like clean)
    if py_params_dict.get("py2hwsw_target", "") == "setup":

        # Copy fdk srcs
        for folder in [
            "libAACdec",
            "libSYS",
            "libArithCoding",
            "libDRCdec",
            "libSACdec",
            "libSBRdec",
            "libMpegTPDec",
            "libFDK",
            "libPCMutils",
        ]:
            shutil.copytree(
                f"{os.path.dirname(os.path.abspath(__file__))}/{folder}",
                f"{py_params_dict['build_dir']}/software/{folder}",
                dirs_exist_ok=True
            )

    return attributes_dict
