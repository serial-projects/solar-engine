import typing

GenericUserdata         = typing.Optional[typing.Any]
GenericInit             = typing.Optional[typing.Callable[[GenericUserdata], None]]
GenericClose            = typing.Optional[typing.Callable[[GenericUserdata], None]]
GenericSetPosition      = typing.Optional[typing.Callable[[GenericUserdata, int], None]]
GenericGetPosition      = typing.Optional[typing.Callable[[GenericUserdata], int]]
GenericGetU8            = typing.Optional[typing.Callable[[GenericUserdata], int]]

T = typing.TypeVar('T')
class Generic(typing.Generic[T]):
    """
    Contains an generic buffer function for the while project.
    """
    def __init__(self, userdata: T):
        self.__userdata:            T = userdata
        self.__init:                typing.Optional[typing.Callable[[T], None]]         = None
        self.__close:               typing.Optional[typing.Callable[[T], None]]         = None
        self.__set_position:        typing.Optional[typing.Callable[[T, int], None]]    = None
        self.__get_position:        typing.Optional[typing.Callable[[T], int]]          = None
        self.__get_u8:              typing.Optional[typing.Callable[[T], int]]          = None

    def attach_init(self, initf: typing.Callable[[T], None]):
        """Attach the init function on the buffer."""
        self.__init = initf
    
    def attach_close(self, closef: typing.Callable[[T], None]):
        """Attach the close function on the buffer."""
        self.__close = closef
    
    def attach_set_position(self, setpositionf: typing.Callable[[T, int], None]):
        """Attach the set position on the buffer."""
        self.__set_position = setpositionf
    
    def attach_get_position(self, getpositionf: typing.Callable[[T], int]):
        """Attach the get position on the buffer."""
        self.__get_position = getpositionf
    
    def attach_get_u8(self, getu8: typing.Callable[[T], int]):
        """Attach the get U8 function on the buffer."""
        self.__get_u8 = getu8
    
    def init(self):
        """Initializes the buffer."""
        if self.__init:
            self.__init(self.__userdata)
    
    def close(self):
        """Closes the buffer."""
        if self.__close:
            self.__close(self.__userdata)
    
    def set_position(self, position: int):
        """Set the buffer."""
        if self.__set_position:
            self.__set_position(self.__userdata, position)
    
    def get_position(self) -> int:
        """Get the buffer."""
        __value: int            = -1
        if self.__get_position:
            __value = self.__get_position(self.__userdata)
        return __value
    
    def get_u8(self) -> int:
        """Get from the buffer an U8."""
        __value: int            = -1
        if self.__get_u8:
            __value = self.__get_u8(self.__userdata)
        return __value