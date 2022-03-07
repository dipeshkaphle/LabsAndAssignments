import java.time.Instant;
import java.time.ZoneId;
import java.time.ZoneOffset;
import java.time.ZonedDateTime;
import java.time.format.DateTimeFormatter;
import java.util.Date;

public class Main {
    public static void main(String arg[]) {
        // set cookie string to expire in a minute
        Instant instant = Instant.now();
        ZoneId zone = ZoneId.of("GMT");
        ZonedDateTime zdt1Min = ZonedDateTime.ofInstant(instant.plusSeconds(60), zone);
        var datePlusOneMin = zdt1Min.format(DateTimeFormatter.RFC_1123_DATE_TIME);
        System.out.println(datePlusOneMin);
    }
}
