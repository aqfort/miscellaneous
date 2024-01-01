package task1;

public abstract class Car implements Vehicle {

    private Integer speed = 0;
    private Integer stage = 0;

    protected String model = "";

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
        System.out.println(this.model + ": beep");
    }

    public void drive(Integer speed) {
        this.speed = speed;
    }

    public Integer getSpeed() {
        return this.speed;
    }

    public Boolean isStock() {
        return stage.equals(0);
    }

    public void tune(Integer stage) {
        this.stage = stage;
    }
}
