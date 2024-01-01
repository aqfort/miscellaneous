package task1;

public class SportsCar extends Car {

    private String pilot = "Anon";

    SportsCar(String model) {
        this.model = model;
    }

    public void setPilot(String pilot) {
        this.pilot = pilot;
    }

    public String getPilot() {
        return this.pilot;
    }
}
