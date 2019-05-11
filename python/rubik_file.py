import pandas as pd

class RubikFile():
    def __init__(self, path):
        """
        path: path to file

        Exemple: "~/Documents/file.h5"
        """
        self.path = path

    def write(self, h5_group, dico):
        """
        h5_group: name to group in h5file
        dico: data to store
        """
        data = {}
        data["data"] = dico
        df = pd.DataFrame.from_dict(data)
        print("Writing...")
        df.to_hdf(self.path, key=h5_group, complevel=9, complib='blosc:zlib')
        print("Write done")

    def read(self, h5_group):
        """
        h5_group: name to group in h5file
        """
        return pd.read_hdf(self.path, h5_group)
