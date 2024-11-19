import org.w3c.dom.*; // объектная модель документа (DOM) --> создание объектов
import javax.xml.parsers.*; // для создания парсеров
// ParserConfigurationException; -- Для обработки ошибок конфигурации парсера ^
import java.io.File; // для работы с файлами
import javax.swing.table.DefaultTableModel;
import javax.xml.transform.*; // для преобразования и записи в XML-документ
import javax.xml.transform.dom.DOMSource; // источник данных DOM для записи
import javax.xml.transform.stream.StreamResult; // класс для записи XML в файл (поток)


/**
 * Класс, содержащий методы для работы с XML-документами.
 */
public class XMLfile {

    /**
     * Метод для загрузки данных из XML-файла и добавления их в таблицу.
     * @param tableModel модель таблицы, куда будут добавлены данные
     * @param file файл XML, откуда будут загружены данные
     */
    public static void loadFromXML(DefaultTableModel tableModel, File file) {
        try {
            // фабрика для создания парсеров
            DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();

            // создаем сам парсер (builder)
            DocumentBuilder builder = factory.newDocumentBuilder();

            Document doc = builder.parse(file); // загружаем и парсим сам файл
            doc.getDocumentElement().normalize(); // нормализуем "чистим после парсинга"

            NodeList nodeList = doc.getElementsByTagName("patient"); // загружаем все узлы пациентов (каждый 'patient')
            tableModel.setRowCount(0); // очищаем таблицу перед загрузкой данных

            // проходимся по каждому элементу patients
            for (int i = 0; i < nodeList.getLength(); i++) {
                Node node = nodeList.item(i); // проходимся по каждому узлу
                if (node.getNodeType() == Node.ELEMENT_NODE) {
                    Element element = (Element) node; // преобразуем каждый узел для возможности работать с аттрибутами

                    // Извлекаем данные из каждого элемента <patient>
                    String name = element.getElementsByTagName("name").item(0).getTextContent();
                    /* getElementsByTagName("name") -- ищем дочерние элемнты с определенным именем
                    *  .item(0) -- берем первый элемент из списка
                    *  */
                    String disease = element.getElementsByTagName("disease").item(0).getTextContent();
                    String doctor = element.getElementsByTagName("doctor").item(0).getTextContent();
                    String specialization = element.getElementsByTagName("specialization").item(0).getTextContent();
                    String date = element.getElementsByTagName("date").item(0).getTextContent();
                    String status = element.getElementsByTagName("status").item(0).getTextContent();

                    // Добавляем данные в модель таблицы
                    tableModel.addRow(new Object[]{name, disease, doctor, specialization, date, status});
                }
            }

        } catch (Exception ex) { // доделать, чтобы делал полноценный вывод; ??
            ex.printStackTrace();
        }
    }

    /**
     * Метод для сохранения данных из таблицы в XML-файл.
     * @param tableModel модель таблицы, из которой будут извлечены данные
     * @param file файл, куда будет записан XML
     */
    public static void saveToXML (DefaultTableModel tableModel, File file) {
        try {
            DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
            DocumentBuilder builder = factory.newDocumentBuilder();
            Document doc = builder.newDocument();
            Element root = doc.createElement("patients"); // корневой элемент
            doc.appendChild(root);

            // проходим по строкам таблицы и создаем элементы <patient>
            for (int row = 0; row < tableModel.getRowCount(); row++) {
                Element patient = doc.createElement("patient");

                // создаем элементы <name>, <disease>, <doctor> и т.д. для каждого пациента
                Element name = doc.createElement("name");
                name.appendChild(doc.createTextNode(tableModel.getValueAt(row, 0).toString()));
                patient.appendChild(name);

                Element disease = doc.createElement("disease");
                disease.appendChild(doc.createTextNode(tableModel.getValueAt(row, 1).toString()));
                patient.appendChild(disease);

                Element doctor = doc.createElement("doctor");
                doctor.appendChild(doc.createTextNode(tableModel.getValueAt(row, 2).toString()));
                patient.appendChild(doctor);

                Element specialization = doc.createElement("specialization");
                specialization.appendChild(doc.createTextNode(tableModel.getValueAt(row, 3).toString()));
                patient.appendChild(specialization);

                Element date = doc.createElement("date");
                date.appendChild(doc.createTextNode(tableModel.getValueAt(row, 4).toString()));
                patient.appendChild(date);

                Element status = doc.createElement("status");
                status.appendChild(doc.createTextNode(tableModel.getValueAt(row, 5).toString()));
                patient.appendChild(status);

                // добавляем <patient> к корневому элементу <patients>
                root.appendChild(patient);
            }
            System.setProperty("javax.xml.transform.TransformerFactory", "com.sun.org.apache.xalan.internal.xsltc.trax.TransformerFactoryImpl");
            TransformerFactory transformerFactory = TransformerFactory.newInstance();
            Transformer transformer = transformerFactory.newTransformer();
            DOMSource source = new DOMSource(doc);
            StreamResult result = new StreamResult(file);

            // Записываем XML в указанный файл
            transformer.transform(source, result);

        } catch (Exception ex) {
            ex.printStackTrace();
        }
    }
}
