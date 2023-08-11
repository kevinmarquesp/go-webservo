package arduino

// That struct encapsulates the necessary information that each servo connected
// to the Arduino board should have; it's used to render the things on the
// frontend side.
type Servoinfo struct {
    Mindeg     int
    Maxdeg     int
    Position   int
    IsAttached bool
}

// List of all servos connected to the Arduino board.
var AllServoinfo []Servoinfo
