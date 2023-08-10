package arduino

type Servoinfo struct {
    Mindeg     int
    Maxdeg     int
    Position   int
    IsAttached bool
}

var AllServoinfo []Servoinfo
