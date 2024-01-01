package task3;

import java.io.*;
import java.nio.file.*;
import java.util.stream.Stream;

public class Grep {

    static void usage() {
        System.err.println("java Grep <substring>" +
                " <optional_starting_directory>");
        System.exit(-1);
    }

    public static void main(String[] args)
            throws IOException {

        if (args.length != 1 && args.length != 2)
            usage();

        Path startingDir;

        if (args.length == 1) {
            startingDir = Paths.get(".");
        } else {
            startingDir = Paths.get(args[1]);
        }

        String pattern = ".*" + args[0].replace(".", "[a-zA-Z0-9.]") + "[a-zA-Z0-9.]*$"; // don't understand, why [^/]
                                                                                         // instead of [a-zA-Z0-9.] is
                                                                                         // forbidden

        System.out.println("Pattern: <" + pattern + ">");

        try (Stream<Path> paths = Files.walk(startingDir).parallel()) {
            paths.map(path -> path.toString()).filter(f -> f.matches(pattern)).forEach(System.out::println);
        }
    }
}
