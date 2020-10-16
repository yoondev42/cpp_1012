
// 디자인 패턴 22가지

// 생성 5가지
//   싱글톤: 오직 한개의 객체를 생성하고, 언제 어디서든 동일한 방법을 통해 접근할 수 있다.
//   추상팩토리: 팩토리를 인터페이스 기반으로 만들어서 교체 가능하게 하자.
//   팩토리메소드: 객체 생성의 정책을 자식이 가상함수로 정의하게 하자.
//   프로토타입: 객체의 복제를 다형적으로 구현한다.
//   빌더

// 구조 7가지
//   어답터, 프락시, 플라이웨이트, 컴포지트 - OK
//   브릿지, 퍼사드, 데코레이터

// 행위 11가지
//   반복자, 방문자      => 컨테이너(복합객체)의 내부 구조에 상관없이 열거(반복자) / 연산(방문자)
//   관찰자, 책임의 전가  => 이벤트 - 관찰자(전파) / 책임의 전가(전달)
//   템플릿 메소드 / 전략  => 정책에 대응하는 패턴 - 공통성과 가변성의 분리
//   커맨드 => 명령 캡슐화
//   상태, 메멘토, 중재자, (인터프리터)

// SOLID
//   정리한 사람: 로버트 C 마틴
//  - SRP(Single Responsiblity, 단일책임원칙):모듈은 단 하나의 책임을 가져야 한다.
//  - OCP(Open Close, 개방폐쇄원칙):모듈은 확장에는 열려있고, 수정에는 닫혀 있어야 한다.
//  - LSP(Liskov Substitution, 리스코프치환원칙):자식 클래스는 부모 클래스로 대체할 수 있어야 한다.
//  - ISP(Interface Segregation, 인터페이스분리원칙):범용 인터페이스보다 세분화된 인터페이스가 낫다.
//  - DIP(Dependency Inversion, 의존관계역전원칙):클라이언트는 구체적인 타입에 의존하는 것이 아니라 인터페이스나 추상 클래스에 의존해야 한다.