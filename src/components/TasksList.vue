<template>
    <div>
      <div class="flex bg-blue-100">
        <main class="flex-1 p-4">
          <div v-if="currentTab === 'tasks'">
            <h2 class="text-2xl mb-4">Список задач</h2>
            <table class="min-w-full bg-white">
              <thead class="bg-blue-300">
                <tr>
                  <th class=" w-1/3 px-4 py-2">Название задачи</th>
                  <th class=" w-1/6 px-4 py-2">Проект</th>
                  <th class=" w-1/6 px-4 py-2">Активный</th>
                  <th class="w-1/3 px-4 py-2 text-center">Действия</th>
                </tr>
              </thead>
              <tbody>
                <tr v-for="(task, index) in tasks[nowIndex]" :key="task.name" class="border-t">
                  <td class="px-4 py-2">
                    <input v-if="editingIndex === index" v-model="editTaskData.name" class="w-full px-2 py-1 border rounded" />
                    <span v-else>{{ task.name }}</span>
                  </td>
                  <td class="px-4 py-2">
                    <div v-if="editingIndex === index">
                      <select v-model="editTaskData.name_project" class="w-full px-2 py-1 border rounded" @change="handleProjectChange">
                        <option v-for="project in projects" :key="project.name" :value="project.name">{{ project.name }}</option>
                        <option value="new">Добавить новый проект</option>
                      </select>
                      <input v-if="isAddingNewProject" v-model="newProjectName" class="w-full px-2 py-1 border rounded mt-2" placeholder="Введите название нового проекта" />
                    </div>
                    <span v-else>{{ task.name_project }}</span>
                  </td>
                  <td class="px-4 py-2">
                    <input type="checkbox" v-if="editingIndex === index" v-model="editTaskData.active" />
                    <span v-else>{{ task.active ? 'Да' : 'Нет' }}</span>
                  </td>
                  <td class="px-4 py-2 text-center">
                    <button  @click="editTask(index, nowIndex)" class="text-blue-500 mr-2" v-if="editingIndex !== index && task.active===true">✏️</button>
                    <button @click="deleteTask(index, nowIndex)" class="text-red-500 mr-2">🗑️</button>
                    <button @click="saveTask(index, nowIndex)" class="text-green-500 mr-2" v-if="editingIndex === index">💾</button>
                    <button @click="cancelEdit()" class="text-red-500 mr-2" v-if="editingIndex === index">✖️</button>
                  </td>
                </tr>
                <tr>
                  <td class="px-4 py-2">
                    <input v-model="newTask.name" class="w-full px-2 py-1 border rounded" placeholder="Название" />
                  </td>
                  <td class="px-4 py-2">
                    <div>
                      <select v-model="newTask.name_project" class="w-full px-2 py-1 border rounded" @change="handleNewProjectChange">
                        <option v-for="project in projects" :key="project.name" :value="project.name">{{ project.name }}</option>
                        <option value="new">Добавить новый проект</option>
                      </select>
                      <input v-if="isAddingNewProject" v-model="newProjectName" class="w-full px-2 py-1 border rounded mt-2" placeholder="Введите название нового проекта" />
                    </div>
                  </td>
                  <td class="px-4 py-2 text-center">
                    <input type="checkbox" v-model="newTask.active" />
                  </td>
                  <td class="px-4 py-2 text-center">
                    <button @click="addTask(nowIndex)" class="text-blue-500">➕</button>
                  </td>
                </tr>
              </tbody>
            </table>
            <div v-if="errorMessage" class="mt-4 text-red-500">
              {{ errorMessage }}
            </div>
          </div>
        </main>
      </div>
    </div>
  </template>
  
  <script>
  export default {
    props: {
      nowIndex: {
        type: Number,
        default: 0
      },
      tasks: {
        type: Array
      },
      projects: {
        type: Array,
        required: true
      },
      addProject: {
        type: Function,
        required: true
      }
    },
    data() {
      return {
        currentTab: 'tasks',
        editingIndex: null,
        editTaskData: { name: '', name_project: '', active: false },
        errorMessage: '',
        newTask: { name: '', name_project: '', active: false },
        newProjectName: '',
        isAddingNewProject: false
      };
    },
    methods: {
      validateTaskData(task) {
        if (!task.name || (!task.name_project && !this.newProjectName)) {
          this.errorMessage = 'Названия задачи и проекта не могут быть пустыми.';
          return false;
        }
        if (typeof task.name !== 'string') {
          this.errorMessage = 'Название задачи должно быть текстом.';
          return false;
        }
        if (typeof task.name_project !== 'string' && !this.newProjectName) {
          this.errorMessage = 'Название проекта должно быть текстом.';
          return false;
        }
        this.errorMessage = '';
        return true;
      },
      addTask(nowIndex) {
        if (this.isAddingNewProject && this.newProjectName) {
          this.addProject(this.newProjectName);
          this.newTask.name_project = this.newProjectName;
        }
        if (this.validateTaskData(this.newTask)) {
          this.tasks[nowIndex].push({ ...this.newTask });
          this.newTask = { name: '', name_project: '', active: false };
          this.newProjectName = '';
          this.isAddingNewProject = false;
        }
      },
      editTask(index, nowIndex) {
        this.editingIndex = index;
        this.editTaskData = { ...this.tasks[nowIndex][index] };
        this.isAddingNewProject = false;
        this.newProjectName = '';
      },
      deleteTask(index, nowIndex) {
        this.tasks[nowIndex].splice(index, 1);
      },
      saveTask(index, nowIndex) {
        if (this.isAddingNewProject && this.newProjectName) {
          this.addProject(this.newProjectName);
          this.editTaskData.name_project = this.newProjectName;
        }
        if (this.validateTaskData(this.editTaskData)) {
          this.tasks[nowIndex].splice(index, 1, this.editTaskData);
          this.cancelEdit();
        }
      },
      cancelEdit() {
        this.editingIndex = null;
        this.editTaskData = { name: '', name_project: '', active: false };
        this.errorMessage = '';
        this.isAddingNewProject = false;
        this.newProjectName = '';
      },
      handleProjectChange(event) {
        this.isAddingNewProject = event.target.value === 'new';
      },
      handleNewProjectChange(event) {
        this.isAddingNewProject = event.target.value === 'new';
      }
    }
  };
  </script>
  
  <style scoped>
  /* Add any additional styles here */
  </style>
  