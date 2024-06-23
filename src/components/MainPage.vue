<template>
  <div>
    <header class="bg-blue-300 p-4 flex items-center justify-between">
      <div class="flex items-center">
        <img src="@/assets/iconka.png" alt="iconka" class="w-12 h-12 mr-2" />
        <h1 class="text-white text-xl">Корпоративный портал учета рабочего времени</h1>
      </div>
      <button @click="currentTab = 'addEmployee'" class="text-white">Новый сотрудник</button>
    </header>
    <div class="flex bg-blue-100">
      <aside class="bg-blue-100 w-1/4 p-4 h-screen overflow-y-auto">
        <div class="flex items-center mb-4">
          <svg class="w-6 h-6 mr-2 text-blue-600" fill="currentColor" viewBox="0 0 24 24">
            <path d="M16 11c1.657 0 3-1.343 3-3S17.657 5 16 5s-3 1.343-3 3 1.343 3 3 3zm2 1h-4c-2.21 0-4 1.79-4 4v4h12v-4c0-2.21-1.79-4-4-4z" />
            <path d="M6 11c1.657 0 3-1.343 3-3S7.657 5 6 5 3 6.343 3 8s1.343 3 3 3zm2 1H4c-2.21 0-4 1.79-4 4v4h8v-4c0-2.21-1.79-4-4-4z" />
          </svg>
          <span>Список сотрудников</span>
        </div>
        <ul>
          <li v-for="(employee, index) in employees" :key="index" class="mb-2">
            <a @click="currentTab = 'Employee'; nowIndex = index" class="block p-2 bg-white rounded shadow" href="#">
              {{ employee.name }}
            </a>
          </li>
        </ul>
      </aside>
      <main class="flex-1 p-4">
        <nav class="flex space-x-4 mb-4">
          <button @click="currentTab = 'projects'"
            :class="{'bg-blue-300 text-white': currentTab === 'projects', 'text-blue-500': currentTab !== 'projects'}"
            class="px-4 py-2 rounded">
            Проекты
          </button>
          <button @click="currentTab = 'tasks';" :class="{'bg-blue-300 text-white': currentTab === 'tasks', 'text-blue-500': currentTab !== 'tasks'}"
            class="px-4 py-2 rounded">
            Задачи
          </button>
          <button @click="currentTab = 'transactions'"
            :class="{'bg-blue-300 text-white': currentTab === 'transactions', 'text-blue-500': currentTab !== 'transactions'}"
            class="px-4 py-2 rounded">
            Проводки
          </button>
        </nav>
        <div v-if="currentTab === 'addEmployee'">
          <h2 class="text-2xl mb-4">Добавление сотрудника</h2>
          <ul>
            <label for="name">Введите имя и фамилию нового сотрудника:</label>
            <input type="text" v-model="newEmployees.name" class="px-3 py-1 mt-2 border border-gray-300 rounded-lg" required />
          </ul>
          <nav class="flex space-x-4 mb-4">
            <button @click="addEmployees(); currentTab = 'empty';"
              class="bg-blue-300 text-white px-4 py-2 rounded mb-2 mt-4 space-x-4">
              Сохранить
            </button>
            <button @click="currentTab = 'empty';"
              class="bg-blue-300 text-white px-7 py-2 rounded mb-2 mt-4">
              Отмена
            </button>
          </nav>
        </div>
        <div v-if="currentTab === 'Employee'">
          <h2 class="text-2xl mb-4">{{ employees[nowIndex].name }}</h2>
          <nav class="flex space-x-4 mb-4">
            <button @click="deleteEmployees(nowIndex); currentTab = 'empty';"
              :class="{'text-blue-500': currentTab === 'tasks', 'bg-blue-300 text-white': currentTab !== 'tasks'}"
              class="px-7 py-2 rounded mb-2 mt-4 space-x-4">
              Удалить
            </button>
          </nav>
        </div>
        <div v-if="currentTab === 'empty'"></div>
        <div v-if="currentTab === 'tasks'">
          <TasksListVue v-bind:tasks="tasks" v-bind:projects="projects" v-bind:nowIndex="nowIndex" v-bind:addProject="addProject" />
        </div>
        <div v-if="currentTab === 'projects'">
          <ProjectsListVue v-bind:projects="projects" v-bind:nowIndex="nowIndex" />
        </div>
        <div v-if="currentTab === 'transactions'">
          <Transactions
            :transactions="transactions"
            :tasks="tasks[nowIndex]"
            :nowIndex="nowIndex"
            :addTask="addTask"
          />
        </div>
        <router-view />
      </main>
    </div>
  </div>
</template>

<script>
import TasksListVue from "./TasksList.vue";
import ProjectsListVue from '../components/ProjectsList.vue';
import Transactions from "./Transactions.vue";
import EmployeeVue from "./Employee.vue";

export default {
  components: {
    TasksListVue,
    ProjectsListVue,
    Transactions,
    EmployeeVue
  },
  data() {
    return {
      currentTab: 'tasks',
      newСhapter: [],
      tasks: [[
        { name: 'Название1', name_project: 'Проект1', active: true },
        { name: 'Название2', name_project: 'Проект1', active: true },
        { name: 'Название3', name_project: 'Проект2', active: true },
        { name: 'Название4', name_project: 'Проект3', active: false },
        { name: 'Название5', name_project: 'Проект3', active: true }
      ], [], [], [], [], []],
      transactions: [[
        { date: '2024-01-01', hours: 1, description: 'Описание1', task: 'Задача1' },
        { date: '2024-02-02', hours: 7, description: 'Описание2', task: 'Задача2' },
        { date: '2024-03-03', hours: 2, description: 'Описание3', task: 'Задача3' },
        { date: '2024-04-04', hours: 3, description: 'Описание4', task: 'Задача4' },
        { date: '2024-05-05', hours: 4, description: 'Описание5', task: 'Задача5' },
        { date: '2024-06-06', hours: 5, description: 'Описание6', task: 'Задача6' }
      ], [], [], [], [], []],
      projects: [
        { name: 'Название1', code: 1, active: true },
        { name: 'Название2', code: 2, active: true },
        { name: 'Название3', code: 3, active: true },
        { name: 'Название4', code: 4, active: false },
        { name: 'Название5', code: 5, active: true }
      ],
      employees: [
        { name: 'Мила Степанова' },
        { name: 'Александр Тарасов' },
        { name: 'Софья Сергеева' },
        { name: 'Глеб Петров' },
        { name: 'Василий Зубов' },
        { name: 'Дарья Гусева' }
      ],
      newEmployees: { name: '' },
      nowEmployee: { name: 'iii' },
      nowIndex: 0,
    };
  },
  methods: {
    addEmployees() {
      if (this.newEmployees.name) {
        this.employees.push({ ...this.newEmployees });
        this.newEmployees = { name: '' };
        this.tasks.push(this.newСhapter);
        this.transactions.push(this.newСhapter);
      }
    },
    deleteEmployees(index) {
      this.employees.splice(index, 1);
    },
    addProject(projectName) {
      const newProject = {
        name: projectName,
        code: this.projects.length + 1,
        active: true
      };
      this.projects.push(newProject);
    },
    addTask(task) {
      if (!this.tasks[this.nowIndex].some(t => t.name === task)) {
        this.tasks[this.nowIndex].push({ name: task, name_project: '', active: true });
      }
    }
  }
};
</script>

<style scoped>
/* Add any additional styles here */
</style>
