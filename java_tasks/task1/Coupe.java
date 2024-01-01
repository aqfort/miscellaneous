package task1;

public class Coupe extends Car {

    private Boolean pano = false;

    Coupe(String model, Boolean pano) {
        this.model = model;
        this.pano = pano;
    }

    public Boolean hasPano() {
        return this.pano;
    }
}
