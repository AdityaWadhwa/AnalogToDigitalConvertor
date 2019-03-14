# AnalogToDigitalConvertor
A circuit that helps create a single slope ADC for device such as PLDs

This repository contains the circuit for creating a single slope ADC for devices such as PLDs that do not have ADCs.

The circuit contains a capacitor being charged by a constant current source which was created using a LM317 voltage regulator. The  voltage of the capacitor is connected to the non inverting input of the a voltage comparator, the LM311 and the inverting input of the compatotor is connected to the analog voltage that we would like to measure, such as the sweep arm of a potentiometer. 

The rate of increase of voltage of the capacitor is linear, which is essential as we must run a counter internally at the exact same speed. When the voltage of the capacitor rises even slightly above the reference voltage, we get a HIGH at the output of the comparator, this can be understood by a Digital Logic Device such as a PLD.

When the Comparator voltage goes HIGH, the count value is latched, this count value is the ADC value; and the transistor connected in parallel to the capacitor is turned ON to help discharge the Capacitor, then we wait until the Capacitor is completely discharged and then start charging the capacitor again.

The current commit contains the circuit and an Arduino code to test the working of the ADC.

The project is developed under the guidance of Mr. D.V Gadre, CEDT lab in Netaji Subhas Institute of Technology (now, Netaji Subhas University of Technology).
