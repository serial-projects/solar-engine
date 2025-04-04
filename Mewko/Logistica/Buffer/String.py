from .Generic import Generic

class StringInterface:
    def __init__(self, value: str): 
        self.__value: str = value
        self.__position: int = 0
    
    def init(self):
        pass
    
    def close(self):
        pass
        
    def set_position(self, position: int):
        self.__position = position
    
    def get_position(self) -> int:
        return self.__position

    def get_u8(self) -> int:
        __value: int        = -1
        if len(self.__value) > self.__position:
            __value: int = ord(self.__value[self.__position])
            self.__position = self.__position + 1
        return __value

class String(Generic[StringInterface]):
    def __init__(self, value: str):
        self.__interface: StringInterface = StringInterface(value)
        super().__init__(self.__interface)
        self.attach_init            (lambda si: si.init())
        self.attach_close           (lambda si: si.close())
        self.attach_set_position    (lambda si, pos: si.set_position(pos))
        self.attach_get_position    (lambda si: si.get_position())
        self.attach_get_u8          (lambda si: si.get_u8())