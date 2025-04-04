from .Generic import Generic
import typing, io

class FileGenericInterface:
    def __init__(self, path: typing.Optional[str]):
        self.__path: typing.Optional[str]                   = path
        self.__pointer: typing.Optional[typing.BinaryIO]    = None
        self.__position: int = 0

    def init(self):
        if self.__path:
            self.__pointer = open(self.__path, "rb")
    
    def close(self):
        if self.__pointer:
            self.__pointer.close()
        
    def set_position(self, position: int):
        if self.__pointer:
            self.__pointer.seek(io.SEEK_SET, position)
            self.__position = position
    
    def get_position(self) -> int:
        value: int          = -1
        if self.__pointer:
            value = self.__position
        return value

    def get_u8(self) -> int:
        __value: int        = -1
        if self.__pointer:
            __return_value: bytes = self.__pointer.read(1)
            if __return_value != b'':
                __value = int.from_bytes(__return_value)
        return __value

class File(Generic[FileGenericInterface]):
    def __init__(self, path: str):
        self.__interface: FileGenericInterface = FileGenericInterface(path)
        super().__init__(self.__interface)
        self.attach_init                (lambda fgi: fgi.init())
        self.attach_close               (lambda fgi: fgi.close())
        self.attach_set_position        (lambda fgi, setpos: fgi.set_position(setpos))
        self.attach_get_position        (lambda fgi: fgi.get_position())
        self.attach_get_u8              (lambda fgi: fgi.get_u8())