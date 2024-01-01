package task1;

public abstract class Truck implements Vehicle {

    private Integer speed = 0;
    private Boolean loaded = false;
    private Integer weight = 0;

    public String model = "";

    @Override
    public void start() {
        System.out.println(this.model + ": start");
    }

    @Override
    public void stop() {
        this.speed = 0;
        System.out.println(this.model + ": stop");
    }

    @Override
    public void honk() {
        System.out.println(this.model + ": BEEP");
    }

    public void drive(Integer speed) {
        this.speed = speed;
    }

    public Integer getSpeed() {
        return this.speed;
    }

    public void load(Integer weight) {
        this.weight = weight;
        loaded = true;
    }

    public void unload() {
        this.weight = 0;
        loaded = false;
    }

    public Boolean isLoaded() {
        return this.loaded;
    }

    public Integer weight() {
        return this.weight;
    }
}
